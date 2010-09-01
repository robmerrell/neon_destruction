#include "gameplay_scene.h"

#include <iostream>

bool GameplayScene::finished_level = false;
bool GameplayScene::accel_control = false;
bool GameplayScene::cannon_dimmed = false;

GameplayScene::GameplayScene() {
  menu = new Menu();
  menu_open = false;
  dialog_open = false;
  level_reset = false;
  go_to_level = false;
  quit = false;
  score = 0;
  draw_physics = false;
  in_loop = false;
  frame = 0;
  joystick = NULL;
    
  // set up the Chipmunk physics space
  cpInitChipmunk();
  space = cpSpaceNew();
  space->iterations = 10;
  space->elasticIterations = 10;
	space->gravity = cpv(0, GRAVITY_RATE);
	
  staticBody = cpBodyNew(INFINITY, INFINITY);
  
  // by default ignore collisions between the cannon and the balls and goals
  cpSpaceAddCollisionHandler(space, GRAVITY_SWITCH_COLLISION, BALL_COLLISION, gravity_switch_solver, NULL, NULL, NULL, NULL);
  cpSpaceAddCollisionHandler(space, ACCEL_SWITCH_COLLISION, BALL_COLLISION, accel_switch_solver, NULL, NULL, NULL, NULL);
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
  
  delete menu;
  menu = NULL;
}

bool GameplayScene::setup() {
  bool stop = false;
  defineBorder(true, true, true, true);
  
  // load a level
  loadLevel(LevelData::Instance()->getCurrentDetails().filename);
  
  // start the game loop
  while(!quit && !stop) {
    gameLoop();
    if (!LevelData::Instance()->getCurrentLevel().empty())
      stop = replaceLevel(LevelData::Instance()->getCurrentDetails().filename);
    else
      stop = true;
  }
  
  return quit;
}


void GameplayScene::gameLoop() {
  bool paused = false;
  in_loop = true;
  float angle, radians;
  cpVect ball_start_coords, calc_vect;

  // add a blank crosshair
  CrossHair *crosshair = new CrossHair(-100, -100);
  addObject(crosshair);
  
  // accel
  float xForce = 0.0f;
  float yForce = 0.0f;
  
  // timestepping
  float accumulator = 0.0f;
  int millistep = 16;
  float timeStep = float(millistep)/1000;
  fps.start();
  particle_timer.start();
  animation_ticks = 0;
    
  while (in_loop) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (accel_control) {
      xForce = (float) SDL_JoystickGetAxis(joystick, 1) / 32768.0;
      yForce = ((float) SDL_JoystickGetAxis(joystick, 0) / 32768.0) * -1.0f;

      space->gravity = cpv(xForce * ACCEL_GRAVITY_RATE, yForce * ACCEL_GRAVITY_RATE);
    }
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        in_loop = false;
        quit = true;
      } else if (event.type == SDL_ACTIVEEVENT) {
        if (event.active.gain == 1 && event.active.state & SDL_APPACTIVE) {
          paused = false;
        } else if (event.active.gain == 0 && event.active.state & SDL_APPACTIVE) {
          paused = true;
        }
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == PDLK_GESTURE_BACK && !dialog_open) {
          if (menu_open) {
            menu_open = false;
            menu->setLevelPicker(false);
          } else
            menu_open = true;
        }
        
      } else if (event.type == SDL_MOUSEMOTION) {
        // rotate the turret
        cpVect event_coords = translatedMouseCoords(event.motion.x, event.motion.y);
        
        Cannon *cannon = (Cannon*)findObject(CANNON_TAG);
        if (cannon != NULL) {
          angle = getInvertedMouseAngle(cpv(cannon->getX() + 64.0f, cannon->getY() + 51.0f), event_coords);
          cannon->rotateTurret(angle);
        }
      } else if (event.type == SDL_MOUSEBUTTONUP) {
        cpVect event_coords = translatedMouseCoords(event.button.x, event.button.y);
        
        if (!menu_open && !dialog_open && !accel_control) {
          SoundManager::Instance()->playCannon();
        
          // reposition the crosshair
          crosshair->setX(event_coords.x);
          crosshair->setY(event_coords.y);
        
          // find the cannon game object
          Cannon *cannon = (Cannon*)findObject(CANNON_TAG);
          if (cannon != NULL) {
            score++;
          
            stringstream ss;
            ss << score;
            TextureString *score_string = (TextureString*)findObject(SCORE_STRING_TAG);
            if (score_string != NULL) score_string->setMessage(string("Shots: " + ss.str()));
          
            radians = getMouseRadians(cpv(cannon->getX() + 64.0f, cannon->getY() + 51.0f), event_coords);

            ball_start_coords.x = cannon->getX() + 64.0f;
            ball_start_coords.y = cannon->getY() + 51.0f;
          
            // calculate the starting coordinates for the ball
            calc_vect = cpvmult(cpvforangle(radians), 50);
            ball_start_coords.x += calc_vect.x;
            ball_start_coords.y -= calc_vect.y;
        
            // add an ammo object and give it an impulse
            Ball *ball = new Ball(ball_start_coords.x, ball_start_coords.y);
            ball->definePhysics(space);
            ball->applyImpulse(event_coords, ball_start_coords, space->gravity.y);
            addObject(ball);
            ball_count++;
          }
        } else if (dialog_open) {
          // resume
          if (event_coords.x >= 136 && event_coords.x <= 329 && event_coords.y >= 236 && event_coords.y <= 289) {
            dialog_open = false;
            
            // delete the menu
            vector<Sprite*>::iterator sprite;
            for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
              if ((*sprite)->getTag() == DIALOG_TAG) {
                (*sprite)->destroy(space);
                delete (*sprite);
                (*sprite) = NULL;
                
                objects.erase(sprite);
              }
            }
          }
        } else if (menu_open) {
          if (!menu->getLevelPicker()) {
            // reset button
            if (event_coords.x >= 59 && event_coords.x <= 231 && event_coords.y >= 26 && event_coords.y <= 78) {
              finished_level = true;
              level_reset = true;
            }
          
            // go to level button
            if (event_coords.x >= 250 && event_coords.x <= 423 && event_coords.y >= 26 && event_coords.y <= 78) {
              menu->setLevelPicker(true);
            }
          
            // sound on
            if (event_coords.x >= 218 && event_coords.x <= 262 && event_coords.y >= 140 && event_coords.y <= 181) {
              SoundManager::Instance()->soundOn(true);
            }
          
            // sound off
            if (event_coords.x >= 325 && event_coords.x <= 378 && event_coords.y >= 140 && event_coords.y <= 181) {
              SoundManager::Instance()->soundOn(false);
            }
          } else {
            // first
            if (event_coords.x >= 59 && event_coords.x <= 420 && event_coords.y >= 16 && event_coords.y <= 54) {
              int pos = menu->getPage()*3 + 1;
              LevelDetails details = LevelData::Instance()->getDetailsByPosition(pos);
              
              bool can_show = false;
              if (details.completed == "1") can_show = true;
              if (pos != 1) {
                LevelDetails prev_level = LevelData::Instance()->getDetailsByPosition(pos-1);
                if (prev_level.completed == "1") can_show = true;
              }
                            
              if (can_show) {              
                finished_level = true;
                go_to_level = true;
              
                LevelData::Instance()->setCurrentLevel(details.id);
                menu->setLevelPicker(false);
              }
            }
            
            // second
            if (event_coords.x >= 59 && event_coords.x <= 420 && event_coords.y >= 82 && event_coords.y <= 120) {
              if (menu->getPage()*3+1 < LevelData::Instance()->getCoreLevelCount()) {
                int pos = menu->getPage()*3 + 2;
                LevelDetails details = LevelData::Instance()->getDetailsByPosition(pos);
                
                bool can_show = false;
                if (details.completed == "1") can_show = true;
                LevelDetails prev_level = LevelData::Instance()->getDetailsByPosition(pos-1);
                if (prev_level.completed == "1") can_show = true;
                
                if (can_show) {
                  finished_level = true;
                  go_to_level = true;
                  
                  LevelData::Instance()->setCurrentLevel(details.id);
                  menu->setLevelPicker(false);
                }
              }
            }
            
            // third
            if (event_coords.x >= 59 && event_coords.x <= 420 && event_coords.y >= 147 && event_coords.y <= 185) {
              if (menu->getPage()*3+2 < LevelData::Instance()->getCoreLevelCount()) {
                int pos = menu->getPage()*3 + 3;
                LevelDetails details = LevelData::Instance()->getDetailsByPosition(pos);
                
                bool can_show = false;
                if (details.completed == "1") can_show = true;
                LevelDetails prev_level = LevelData::Instance()->getDetailsByPosition(pos-1);
                if (prev_level.completed == "1") can_show = true;
                
                if (can_show) {
                  finished_level = true;
                  go_to_level = true;
                
                  LevelData::Instance()->setCurrentLevel(details.id);
                  menu->setLevelPicker(false);
                }
              }            
            }
            
            // previous
            if (event_coords.x >= 70 && event_coords.x <= 111 && event_coords.y >= 239 && event_coords.y <= 281) {
              menu->prevPage();
            }
            
            // next
            if (event_coords.x >= 348 && event_coords.x <= 392 && event_coords.y >= 239 && event_coords.y <= 281) {
              menu->nextPage();
            }
          }
          
          // resume
          if (event_coords.x >= 136 && event_coords.x <= 329 && event_coords.y >= 236 && event_coords.y <= 289) {
            menu_open = false;
            menu->setLevelPicker(false);
          }
        }
      }
    }
    
    animation_ticks = fps.get_ticks();
    if (animation_ticks > 32) animation_ticks = 32;
    accumulator += animation_ticks;
    fps.start();
    
    while (accumulator >= millistep) {
      if (!menu_open && !dialog_open && !paused) {
        cpSpaceStep(space, timeStep);
        cpSpaceHashEach(space->activeShapes, &updateShape, NULL);
      }
      accumulator -= millistep;
    }
    
    glDisable(GL_BLEND);
    
    // draw the background
    if (!paused) {
      moveBackground(animation_ticks);
      updateAnimation(animation_ticks);
      drawBackground();
    }
    
    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
    
    if (!cannon_dimmed && accel_control) {
      Cannon *to_dim = (Cannon*)findObject(CANNON_TAG);
      to_dim->setAlpha(0.4f);
      
      AccelSwitch *ac = (AccelSwitch*)findObject(ACCEL_SWITCH_TAG);
      ac->block();
      
      crosshair->setX(-100.0f);
      crosshair->setY(-100.0f);
      
      cannon_dimmed = true;
    }

    // display
    if (!paused) {
      vector<Sprite*>::iterator sprite;
      for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
        if ((*sprite)->getTag() == BALL_TAG) {
           (*sprite)->emitParticles(particle_timer.get_ticks());
           (*sprite)->manageParticles(particle_timer.get_ticks(), fps.get_ticks());
        }
      
        // move platforms if needed
        if (!menu_open && !dialog_open) {
          if ((*sprite)->getTag() == PLATFORM_TAG) {
            if ((*sprite)->moveable()) {
              (*sprite)->move(animation_ticks);
            }
          }
        }
      
        if (!menu_open && !dialog_open)
          (*sprite)->display();
        else if (dialog_open) {
          if ((*sprite)->getTag() == DIALOG_TAG) {
            (*sprite)->display();
          }
        }
      }
    
      if (draw_physics)
        draw_chipmunk(space);
    
      if (menu_open) {
        menu->display();
      }
    
      // update the screen
      SDL_GL_SwapBuffers();
    
    if (ball_count > 15) {
      for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
        if ((*sprite)->getTag() == BALL_TAG) {
          ball_count--;
          
          (*sprite)->destroy(space);
          delete (*sprite);
          (*sprite) = NULL;
          
          objects.erase(sprite);
          
          break;
        }
      }
    }
   
      if (finished_level) {
        SoundManager::Instance()->playLevelEnd();
      
        for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
          (*sprite)->setAnimationState(ANIMATE_FADE_OUT);
        }
      
        Cannon *cannon = (Cannon*)findObject(CANNON_TAG);
      
        if (cannon->getAlpha() <= 0.0f || level_reset || go_to_level) {
          finished_level = false;
          in_loop = false;
          if (!level_reset && !go_to_level) {
            stringstream score_stream;
            score_stream << score;
          
            LevelData::Instance()->updateCurrentScore(score_stream.str());
            LevelData::Instance()->setCurrentLevel(LevelData::Instance()->getNextLevel());
            LevelData::Instance()->writeUserData();
          } else
            level_reset = false;
        }
      }
    
      frame++;
    }
  }
}


void GameplayScene::loadLevel(string level_file) {
  ball_count = 0;
  has_cannon = false;
  has_goal = false;
  string path = "levels/";
  
  TiXmlDocument level_data(path.append(level_file).c_str());
  level_data.LoadFile();
  
  string id, size, x, y, angle, type, physics, width, height, radius, dir, impulse_x, impulse_y, num, text, mass, elasticity, friction;
  string min_pos, max_pos, direction;
  string fixed = "";
  string body1, body2, body1_x, body1_y, body2_x, body2_y;
  cpBody *pinbody1, *pinbody2;
  Box *box;
  Platform *platform;
  Circle *circle;
  Triangle *triangle;
  Gear *gear;
  GravitySwitch *gravity_switch;
  AccelSwitch *accel_switch;
  int gravity_direction = GRAVITY_DOWN;
  
  TiXmlNode* level = level_data.FirstChild("level");
  TiXmlNode* object_node;
  
  if (LevelData::Instance()->getCurrentDetails().id == "1" || LevelData::Instance()->getCurrentDetails().id == "2" || LevelData::Instance()->getCurrentDetails().id == "4" || LevelData::Instance()->getCurrentDetails().id == "8") {
    Dialog *testd = new Dialog(LevelData::Instance()->getCurrentDetails().id);
    addObject(testd);
    dialog_open = true;
  }

  if (LevelData::Instance()->getCurrentDetails().filename != "end_scene.xml") {    
    TextureString *level_name = new TextureString(0.0f, 0.0f, LevelData::Instance()->getCurrentDetails().name);
    level_name->setTag(LEVEL_STRING_TAG);
    addObject(level_name);
        
    if (level->ToElement()->Attribute("name") != NULL) {
      level_name->setMessage(level->ToElement()->Attribute("name"));
    }
    
    TextureString *score_string = new TextureString(350.0f, 0.0f, "Shots: 0");
    score_string->setTag(SCORE_STRING_TAG);
    addObject(score_string);
  
    string best = "Best: ";
    best.append(LevelData::Instance()->getCurrentDetails().score);
    TextureString *best_score_string = new TextureString(350.0f, 20.0f, best);
    addObject(best_score_string);
  } else {
    TextureString *final_score = new TextureString(125.0f, 180.0f, LevelData::Instance()->getFinalScore());
    addObject(final_score);
  }
  
  for (object_node = level->FirstChild(); object_node != 0; object_node = object_node->NextSibling() ) {
    if (object_node->ToElement()->Attribute("type") == string("CANNON") && !has_cannon) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Cannon *cannon = new Cannon(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      
      if (object_node->ToElement()->Attribute("orientation") != NULL) {
        angle = object_node->ToElement()->Attribute("orientation");
        cannon->setOrientation(angle);
      }
      
      addObject(cannon);
      has_cannon = true;
    } else if (object_node->ToElement()->Attribute("type") == string("GOAL")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Goal *goal = new Goal(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      
      if (object_node->ToElement()->Attribute("mass") != NULL) {
        mass = object_node->ToElement()->Attribute("mass");
        goal->setMass(strtof(mass.c_str(), NULL));
      }
      
      if (object_node->ToElement()->Attribute("elasticity") != NULL) {
         elasticity = object_node->ToElement()->Attribute("elasticity");
         goal->setElasticity(strtof(elasticity.c_str(), NULL));
       }
      
      goal->definePhysics(space);
      addObject(goal);
      has_goal = true;
    } else if (object_node->ToElement()->Attribute("type") == string("TEXTURE")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      num = object_node->ToElement()->Attribute("tex");
          
      Image *image = new Image(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL), strtof(width.c_str(), NULL), strtof(height.c_str(), NULL), atoi(num.c_str()));
      
      if (object_node->ToElement()->Attribute("angle") != NULL) {
        angle = object_node->ToElement()->Attribute("angle");
        image->setAngle(strtof(angle.c_str(), NULL));
      }
  
      addObject(image);
    } else if (object_node->ToElement()->Attribute("type") == string("STRING")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      text = object_node->ToElement()->Attribute("text");

      TextureString *string = new TextureString(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL), text);
      addObject(string);
    } else if (object_node->ToElement()->Attribute("type") == string("GEAR")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      angle = object_node->ToElement()->Attribute("angle");
      
      gear = new Gear();
      
      if (object_node->ToElement()->Attribute("mass") != NULL) {
        mass = object_node->ToElement()->Attribute("mass");
        gear->setMass(strtof(mass.c_str(), NULL));
      }
      
      gear->setX(strtof(x.c_str(), NULL));
      gear->setY(strtof(y.c_str(), NULL));
      gear->setWidth(strtof(width.c_str(), NULL));
      gear->setAngle(strtof(angle.c_str(), NULL));
      gear->definePhysics(space);
      
      if (object_node->ToElement()->Attribute("id") != NULL) {
        gear->setId(object_node->ToElement()->Attribute("id"));
      }
      
      addObject(gear);

      if (object_node->ToElement()->Attribute("impulse_x") != NULL) {
        impulse_x = object_node->ToElement()->Attribute("impulse_x");
        impulse_y = object_node->ToElement()->Attribute("impulse_y");
        gear->applyImpulse(strtof(impulse_x.c_str(), NULL), strtof(impulse_y.c_str(), NULL));
      }
      
    } else if (object_node->ToElement()->Attribute("type") == string("GRAVITY_SWTICH")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      dir = object_node->ToElement()->Attribute("default_direction");
    
      if (dir == string("up")) {
        gravity_direction = GRAVITY_UP;
        space->gravity = cpv(0, -GRAVITY_RATE);
      } else if (dir == string("down")) {
        gravity_direction = GRAVITY_DOWN;
        space->gravity = cpv(0, GRAVITY_RATE);
      } else if (dir == string("left")) {
        gravity_direction = GRAVITY_LEFT;
        space->gravity = cpv(-GRAVITY_RATE, 0);
      } else if (dir == string("right")) {
        gravity_direction = GRAVITY_RIGHT;
        space->gravity = cpv(GRAVITY_RATE, 0);
      }

      gravity_switch = new GravitySwitch(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL), gravity_direction);
      gravity_switch->definePhysics(space);
      addObject(gravity_switch);
    } else if (object_node->ToElement()->Attribute("type") == string("ACCEL_SWITCH")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");

      accel_switch = new AccelSwitch(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      accel_switch->definePhysics(space);
      addObject(accel_switch);
      
      joystick = SDL_JoystickOpen(0);
    } else if (object_node->ToElement()->Attribute("type") == string("BOX")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      angle = object_node->ToElement()->Attribute("angle");

      // create the actual box
      box = new Box(physics);
      
      if (object_node->ToElement()->Attribute("mass") != NULL) {
        mass = object_node->ToElement()->Attribute("mass");
        box->setMass(strtof(mass.c_str(), NULL));
      }
      
      box->setX(strtof(x.c_str(), NULL));
      box->setY(strtof(y.c_str(), NULL));
      box->setWidth(strtof(width.c_str(), NULL));
      box->setHeight(strtof(height.c_str(), NULL));
      box->setAngle(strtof(angle.c_str(), NULL));
      box->definePhysics(space);
      
      if (object_node->ToElement()->Attribute("id") != NULL) {
        box->setId(object_node->ToElement()->Attribute("id"));
      }
      
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
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      angle = object_node->ToElement()->Attribute("angle");
      
      platform = new Platform(physics);
      
      if (object_node->ToElement()->Attribute("mass") != NULL) {
        mass = object_node->ToElement()->Attribute("mass");
        platform->setMass(strtof(mass.c_str(), NULL));
      }
      
      if (object_node->ToElement()->Attribute("friction") != NULL) {
        friction = object_node->ToElement()->Attribute("friction");
        platform->setFriction(strtof(friction.c_str(), NULL));
      }
      
      if (object_node->ToElement()->Attribute("fixed") != NULL)
        fixed = object_node->ToElement()->Attribute("fixed");
        
      if (object_node->ToElement()->Attribute("inf") != NULL) {
        platform->infiniteMoment();
      }
      
      if (object_node->ToElement()->Attribute("infnocolor") != NULL) {
        platform->infiniteNormalColor();
      }
        
      if (object_node->ToElement()->Attribute("direction") != NULL) {
        min_pos = object_node->ToElement()->Attribute("min_pos");
        max_pos = object_node->ToElement()->Attribute("max_pos");
        direction = object_node->ToElement()->Attribute("direction");
        
        int dir = 0;
        if (direction == string("N")) dir = 1;
        else if (direction == string("E")) dir = 2;
        else if (direction == string("W")) dir = 3;
        
        platform->setMoveable(strtof(min_pos.c_str(), NULL), strtof(max_pos.c_str(), NULL), dir);
      }
        
      // create the platform
      platform->setX(strtof(x.c_str(), NULL));
      platform->setY(strtof(y.c_str(), NULL));
      platform->setWidth(strtof(width.c_str(), NULL));
      platform->setAngle(strtof(angle.c_str(), NULL));
      platform->definePhysics(space);
      if (fixed != "") platform->fix(space);
      addObject(platform);
      
      if (object_node->ToElement()->Attribute("id") != NULL) {
        platform->setId(object_node->ToElement()->Attribute("id"));
      }
      
      if (object_node->ToElement()->Attribute("impulse_x") != NULL) {
        impulse_x = object_node->ToElement()->Attribute("impulse_x");
        impulse_y = object_node->ToElement()->Attribute("impulse_y");
        platform->applyImpulse(strtof(impulse_x.c_str(), NULL), strtof(impulse_y.c_str(), NULL));
      }
      
      fixed = "";
    } else if (object_node->ToElement()->Attribute("type") == string("CIRCLE")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      radius = object_node->ToElement()->Attribute("radius");

      // create the 
      circle = new Circle(physics);
      
      if (object_node->ToElement()->Attribute("elasticity") != NULL) {
        elasticity = object_node->ToElement()->Attribute("elasticity");
        circle->setElasticity(strtof(elasticity.c_str(), NULL));
      }
      
      circle->setX(strtof(x.c_str(), NULL));
      circle->setY(strtof(y.c_str(), NULL));
      circle->setRadius(strtof(radius.c_str(), NULL));
      
      if (object_node->ToElement()->Attribute("mass") != NULL) {
        mass = object_node->ToElement()->Attribute("mass");
        circle->setMass(strtof(mass.c_str(), NULL));
      }
      
      if (object_node->ToElement()->Attribute("id") != NULL) {
        circle->setId(object_node->ToElement()->Attribute("id"));
      }
      
      circle->definePhysics(space);
      addObject(circle);
    } else if (object_node->ToElement()->Attribute("type") == string("PIN")) {
      body1 = object_node->ToElement()->Attribute("body1");
      body1_x = object_node->ToElement()->Attribute("body1_x");
      body1_y = object_node->ToElement()->Attribute("body1_y");
      
      body2 = object_node->ToElement()->Attribute("body2");
      body2_x = object_node->ToElement()->Attribute("body2_x");
      body2_y = object_node->ToElement()->Attribute("body2_y");
      
      vector<Sprite*>::iterator iter;
      for (iter = objects.begin(); iter != objects.end(); iter++) {
        if ((*iter)->getId() == body1) pinbody1 = (*iter)->getBody();
        if ((*iter)->getId() == body2) pinbody2 = (*iter)->getBody();
      }
      
      cpConstraint *cons = cpSpaceAddConstraint(space, cpPinJointNew(
        pinbody1,
        pinbody2,
        cpv(strtof(body1_x.c_str(), NULL), strtof(body1_y.c_str(), NULL)),
        cpv(strtof(body2_x.c_str(), NULL), strtof(body2_y.c_str(), NULL))
      ));
      
      constraints.push_back(cons);
    }
    
  }
}


bool GameplayScene::replaceLevel(string level_file) {
  accel_control = false;
  cannon_dimmed = false;
  space->gravity = cpv(0, GRAVITY_RATE);
  level_reset = false;
  go_to_level = false;
  
  if (joystick != NULL) {
    SDL_JoystickClose(joystick);
    joystick = NULL;
  }
  
  // clear all of the constraints
  vector<cpConstraint*>::iterator cons;
  for (cons = constraints.begin(); cons != constraints.end(); cons++) {  
    cpSpaceRemoveConstraint(space, (*cons));
    cpConstraintFree((*cons));
    (*cons) = NULL;
  }
  constraints.clear();
  
  // free all of the sprites
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    (*iter)->destroy(space);
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
  
  score = 0;
  menu_open = false;
  
  if (!LevelData::Instance()->getCurrentLevel().empty()) {
    loadLevel(level_file);
    return false;
  }
    
  return true;
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
  if (sprite->getTag() == BOX_TAG || sprite->getTag() == GEAR_TAG || sprite->getTag() == PLATFORM_TAG) {
    sprite->setAngle(RAD2DEG(shape->body->a));
  }
}

static int ignore_pre_solve(cpArbiter *arb, cpSpace *space, void *ignore) {
  return 0;
}

static int pre_solve_goal(cpArbiter *arb, cpSpace *space, void *ignore) {
  GameplayScene::finished_level = true;
  return 0;
}

static int gravity_switch_solver(cpArbiter *arb, cpSpace *space, void *ignore) {
  cpShape *a, *b; cpArbiterGetShapes(arb, &a, &b);
  GravitySwitch *sprite = (GravitySwitch*)a->data;
  cpVect gravity;
  
  if (!sprite->processCollision()) return 0;
  sprite->startTimer();
  
  // up and down
  if (sprite->getDirection() == GRAVITY_UP || sprite->getDirection() == GRAVITY_DOWN) {
    if (space->gravity.y < 0) {
      space->gravity = cpv(0, GRAVITY_RATE);
      sprite->setDirection(GRAVITY_DOWN);
    } else {
      space->gravity = cpv(0, -GRAVITY_RATE);
      sprite->setDirection(GRAVITY_UP);
    }
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

static int accel_switch_solver(cpArbiter *arb, cpSpace *space, void *ignore) {
  GameplayScene::accel_control = true;
  return 0;
}
