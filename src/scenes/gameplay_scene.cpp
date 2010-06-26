#include "gameplay_scene.h"

#include <iostream>

bool GameplayScene::finished_level = false;

GameplayScene::GameplayScene() {
  current_level = 1;
  score = 0;
  draw_physics = false;
  in_loop = false;
  frame = 0;
  
  // set up the Chipmunk physics space
  cpInitChipmunk();
  space = cpSpaceNew();
  space->iterations = 10;
  space->elasticIterations = 10;
	space->gravity = cpv(0, GRAVITY_RATE);
	
  staticBody = cpBodyNew(INFINITY, INFINITY);
  
  // by default ignore collisions between the cannon and the balls and goals
  cpSpaceAddCollisionHandler(space, GRAVITY_SWITCH_COLLISION, BALL_COLLISION, gravity_switch_solver, NULL, NULL, NULL, NULL);
  cpSpaceAddCollisionHandler(space, GOAL_COLLISION, BALL_COLLISION, pre_solve_goal, NULL, NULL, NULL, NULL);
  
  // generate the backgrounds
  int x, y = 0;
  srand((unsigned)time(0)); 
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    x = 1 + rand() % (SCREEN_WIDTH);
    y = 1 + rand() % (SCREEN_HEIGHT);

    starfield1[i] = cpv(x, y);
  
    x = 1 + rand() % (SCREEN_WIDTH);
    y = 1 + rand() % (SCREEN_HEIGHT);

    starfield2[i] = cpv(x, y);
  }
  
  defineStarColors();
  
  for (int i = 0; i < STARS_PER_FIELD * 2; i++) {
    starfield_sizes[i] = 1 + rand() % (2);
  }
}

GameplayScene::~GameplayScene() {
  // free all of the physics simulation items
  cpSpaceFreeChildren(space);
  cpSpaceFree(space);
}

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  // load a level
  loadLevel(GAME_LEVELS[current_level-1]);
  // replaceLevel("stack.xml");
  
  // start the game loop
  gameLoop();
  
  replaceLevel("intro.xml");
  
  gameLoop();
}


void GameplayScene::gameLoop() {
  in_loop = true;
  float angle, radians;
  cpVect ball_start_coords, calc_vect;

  // add a blank crosshair
  CrossHair *crosshair = new CrossHair(-100, -100);
  addObject(crosshair);
  
  // timestepping
  float accumulator = 0.0f;
  int millistep = 16;
  float timeStep = float(millistep)/1000;
  fps.start();
  animation_ticks = 0;
    
  while (in_loop) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
      else if (event.type == SDL_MOUSEMOTION) {
        // rotate the turret
        cpVect event_coords = translatedMouseCoords(event.motion.x, event.motion.y);
        
        Cannon *cannon = (Cannon*)findObject(CANNON_TAG);
        if (cannon != NULL) {
          angle = getInvertedMouseAngle(cpv(cannon->getX(), cannon->getY()), event_coords);
          
          if (angle < 17 || angle > 144)
            cannon->rotateTurret(angle);
        }
      } else if (event.type == SDL_MOUSEBUTTONUP) {
        cpVect event_coords = translatedMouseCoords(event.button.x, event.button.y);
        
        // reposition the crosshair
        crosshair->setX(event_coords.x);
        crosshair->setY(event_coords.y);
        
        // find the cannon game object
        Cannon *cannon = (Cannon*)findObject(CANNON_TAG);
        if (cannon != NULL) {
          score++;
          radians = getMouseRadians(cpv(cannon->getX(), cannon->getY()), event_coords);
          
          // calculate the starting coordinates for the ball
          calc_vect = cpvmult(cpvforangle(radians), 30);
          cpVect cannon_coords = cannon->translatedCoords();
          ball_start_coords.x = cannon_coords.x + calc_vect.x;
          ball_start_coords.y = cannon_coords.y - calc_vect.y;
                    
          // add an ammo object and give it an impulse
          Ball *ball = new Ball(ball_start_coords.x, ball_start_coords.y);
          ball->definePhysics(space);
          ball->applyImpulse(event_coords, ball_start_coords);
          addObject(ball);
        }
      }
    }
    
    animation_ticks = fps.get_ticks();
    accumulator += animation_ticks;
    fps.start();
    
    while (accumulator >= millistep) {
      cpSpaceStep(space, timeStep);
      cpSpaceHashEach(space->activeShapes, &updateShape, NULL);
      accumulator -= millistep;
    }
    
    glDisable(GL_BLEND);
    
    // draw the background
    moveBackground(animation_ticks);
    updateAnimation(animation_ticks);
    drawBackground();
    
    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

    // display
    vector<Sprite*>::iterator sprite;
    for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
      (*sprite)->display();
      
      if (draw_physics)
        draw_chipmunk(space);
    }
    
    // update the screen
    SDL_GL_SwapBuffers();
   
    if (finished_level) {
      finished_level = false;
      in_loop = false;
      current_level++;
    }
    
    frame++;
  }
}


void GameplayScene::loadLevel(string level_file) {
  has_cannon = false;
  has_goal = false;
  string path = "levels/";
  
  TiXmlDocument level_data(path.append(level_file).c_str());
  level_data.LoadFile();

  string size, x, y, angle, type, physics, width, height, radius;
  Box *box;
  Platform *platform;
  Circle *circle;
  Triangle *triangle;
  
  TiXmlNode* level = level_data.FirstChild("level");
  TiXmlNode* object_node;
  
  for (object_node = level->FirstChild(); object_node != 0; object_node = object_node->NextSibling() ) {
    if (object_node->ToElement()->Attribute("type") == string("CANNON") && !has_cannon) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Cannon *cannon = new Cannon(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      addObject(cannon);
      has_cannon = true;
    } if (object_node->ToElement()->Attribute("type") == string("GOAL")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Goal *goal = new Goal(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      goal->definePhysics(space);
      addObject(goal);
      has_goal = true;
    } if (object_node->ToElement()->Attribute("type") == string("BOX")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      angle = object_node->ToElement()->Attribute("angle");

      // create the actual box
      box = new Box(physics);
      box->setX(strtof(x.c_str(), NULL));
      box->setY(strtof(y.c_str(), NULL));
      box->setWidth(strtof(width.c_str(), NULL));
      box->setHeight(strtof(height.c_str(), NULL));
      box->setAngle(strtof(angle.c_str(), NULL));
      box->definePhysics(space);
      addObject(box);
    } else if (object_node->ToElement()->Attribute("type") == string("TRIANGLE")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      angle = object_node->ToElement()->Attribute("angle");
      
      // create the actual triangle
      triangle = new Triangle(physics);
      triangle->setX(strtof(x.c_str(), NULL));
      triangle->setY(strtof(y.c_str(), NULL));
      triangle->setWidth(strtof(width.c_str(), NULL));
      triangle->setHeight(strtof(height.c_str(), NULL));
      triangle->setAngle(strtof(angle.c_str(), NULL));
      triangle->definePhysics(space);
      addObject(triangle);
    } else if (object_node->ToElement()->Attribute("type") == string("PLATFORM")) {
      // extract data from XML
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      angle = object_node->ToElement()->Attribute("angle");

      // create the platform
      platform = new Platform();
      platform->setX(strtof(x.c_str(), NULL));
      platform->setY(strtof(y.c_str(), NULL));
      platform->setWidth(strtof(width.c_str(), NULL));
      platform->setAngle(strtof(angle.c_str(), NULL));
      platform->definePhysics(space);
      addObject(platform);
    } else if (object_node->ToElement()->Attribute("type") == string("CIRCLE")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      radius = object_node->ToElement()->Attribute("radius");

      // create the 
      circle = new Circle(physics);
      circle->setX(strtof(x.c_str(), NULL));
      circle->setY(strtof(y.c_str(), NULL));
      circle->setRadius(strtof(radius.c_str(), NULL));
      circle->definePhysics(space);
      addObject(circle);
    }
  }
}


void GameplayScene::replaceLevel(string level_file) {
  // free all of the sprites
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    (*iter)->destroy(space);
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
  
  loadLevel(level_file);
}

void GameplayScene::drawBackground() {
  TexManager::Instance()->unbindTexture();

  int v_count = 0;

  GLfloat star_verts[STARS_PER_FIELD * 4];
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    star_verts[v_count] = starfield1[i].x;
    v_count++;

    star_verts[v_count] = starfield1[i].y;
    v_count++;

    star_verts[v_count] = starfield2[i].x;
    v_count++;

    star_verts[v_count] = starfield2[i].y;
    v_count++;
  }

  glLoadIdentity();
  glTranslatef(0, 0, 0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_POINT_SIZE_ARRAY_OES);
  
  glVertexPointer(2, GL_FLOAT, 0, star_verts);
  glColorPointer(4, GL_FLOAT, 0, starfield_colors);
  glPointSizePointerOES(GL_FLOAT, 0, starfield_sizes);
  glDrawArrays(GL_POINTS, 0, STARS_PER_FIELD * 2);
  
  glDisableClientState(GL_POINT_SIZE_ARRAY_OES);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GameplayScene::moveBackground(int ticks) {
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    starfield1[i].x -= (STAR_FIELD1_SPEED * (ticks * 0.001));
    starfield2[i].x -= (STAR_FIELD2_SPEED * (ticks * 0.001));

    if (starfield1[i].x < 0)
      starfield1[i].x = SCREEN_WIDTH;
    if (starfield2[i].x < 0)
      starfield2[i].x = SCREEN_WIDTH;
  }
}

void GameplayScene::defineStarColors() {
  int random_num, color_index = 0;
  float r,g,b = 1.0f;
  for (int i = 0; i < STARS_PER_FIELD*2; i++) {
    random_num = 1 + rand() % (10);

    // yellow
    if (random_num == 1) {
      r = 1.0f;
      g = 0.99f;
      b = 0.94f;
    }
    // blue
    else if (random_num == 2) { 
      r = 0.9f;
      g = 0.99f;
      b = 1.0f;
    }
    // red
    else if (random_num == 3) {
      r = 1.0f;
      g = 0.9f;
      b = 0.9f;
    }
    // white
    else {
      r = 1.0f;
      g = 1.0f;
      b = 1.0f;
    }
    
    starfield_colors[color_index] = r;
    starfield_colors[color_index + 1] = g;
    starfield_colors[color_index + 2] = b;
    starfield_colors[color_index + 3] = 1.0f;
    
    color_index += 4;
  }
}

void GameplayScene::defineBorder(bool top, bool right, bool bottom, bool left) {
  float border_elasticity = 0.3f;
  float border_friction = 0.5f;
  
  // top border
  if (top) {
    cpShape *border_top = cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(SCREEN_WIDTH, 0), 1.0f);
    border_top->e = border_elasticity; border_top->u = border_friction;
    cpSpaceAddStaticShape(space, border_top);
  }
  
  // right border
  if (right) {
    cpShape *border_right = cpSegmentShapeNew(staticBody, cpv(SCREEN_WIDTH, 0), cpv(SCREEN_WIDTH, SCREEN_HEIGHT), 1.0f);
    border_right->e = border_elasticity; border_right->u = border_friction;
    cpSpaceAddStaticShape(space, border_right);
  }
  
  // bottom border
  if (bottom) {
    cpShape *border_bottom = cpSegmentShapeNew(staticBody, cpv(0, SCREEN_HEIGHT), cpv(SCREEN_WIDTH, SCREEN_HEIGHT), 1.0f);
    border_bottom->e = border_elasticity; border_bottom->u = border_friction;
    cpSpaceAddStaticShape(space, border_bottom);
  }
  
  // left border
  if (left) {
    cpShape *border_left = cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(0, SCREEN_HEIGHT), 1.0f);
    border_left->e = border_elasticity; border_left->u = border_friction;
    cpSpaceAddStaticShape(space, border_left);
  }
  
}



// update a shape's visual representation
void updateShape(void *ptr, void* unused) {
  cpShape *shape = (cpShape*)ptr;
  
  // make sure the shape is constructed correctly
  if(shape == NULL || shape->body == NULL || shape->data == NULL) {
    // add debugging here
    return;
  }
  
  Sprite *sprite = (Sprite*)shape->data;
  
  sprite->setX(shape->body->p.x);
  sprite->setY(shape->body->p.y);
  
  // rotate certain objects
  if (sprite->getTag() == BOX_TAG || sprite->getTag() == TRIANGLE_TAG) {
    sprite->setAngle(RAD2DEG(shape->body->a));
  }
}

static int ignore_pre_solve(cpArbiter *arb, cpSpace *space, void *ignore) {
  return 0;
}

static int pre_solve_goal(cpArbiter *arb, cpSpace *space, void *ignore) {
  cout << "passed" << endl;
  GameplayScene::finished_level = true;
  // cpSpaceRemoveCollisionHandler(space, GOAL_COLLISION, BALL_COLLISION);
  return 0;
}

static int gravity_switch_solver(cpArbiter *arb, cpSpace *space, void *ignore) {
  cpShape *a, *b; cpArbiterGetShapes(arb, &a, &b);
  GravitySwitch *sprite = (GravitySwitch*)a->data;
  cpVect gravity;
  
  // up and down
  if (sprite->getDirection() == GRAVITY_UP || sprite->getDirection() == GRAVITY_DOWN) {
    if (space->gravity.y < 0)
      space->gravity = cpv(0, GRAVITY_RATE);
    else
      space->gravity = cpv(0, -GRAVITY_RATE);
  }
  
  // left and right
  if (sprite->getDirection() == GRAVITY_LEFT || sprite->getDirection() == GRAVITY_RIGHT) {
    if (space->gravity.x <= 0)
      space->gravity = cpv(GRAVITY_RATE, 0);
    else
      space->gravity = cpv(-GRAVITY_RATE, 0);
  }
  
  return 0;
}