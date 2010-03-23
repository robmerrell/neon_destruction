#include "scene.h"

using namespace std;

Scene::Scene() {
  draw_physics = false;
  in_loop = false;
  frame = 0;
  
  // set up the Chipmunk physics space
  cpInitChipmunk();
  space = cpSpaceNew();
  space->iterations = 10;
  space->elasticIterations = 10;
	space->gravity = cpv(0, 100);
	
  staticBody = cpBodyNew(INFINITY, INFINITY);
  
  // by default ignore collisions between the cannon and the balls
  cpSpaceAddCollisionHandler(space, 1, 2, NULL, ignore_pre_solve, NULL, NULL, NULL);
}

// TODO: check this for memory leaks
Scene::~Scene() {
  // free all of the physics simulation items
  cpSpaceFreeChildren(space);
  cpSpaceFree(space);
  
  // free all of the sprites
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
}

void Scene::addObject(Sprite* sprite) {
  objects.push_back(sprite);
}

Sprite* Scene::findObject(int tag) {
  vector<Sprite*>::iterator sprite;
  for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
    if ((*sprite)->getTag() == tag) {
      return *sprite;
    }
  }
  
  return NULL;
}

void Scene::scheduleLoop(int ticks_per_sec) {
  in_loop = true;
  int mouse_x, mouse_y = 0;
    
  while (in_loop) {
    fps.start();
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        
        // find the cannon game object
        Sprite *cannon = findObject(CANNON_TAG);
        if (cannon != NULL) {
          // add an ammo object and give it an impulse
          Ball *ball = new Ball(cannon->getX(), cannon->getY());
          ball->definePhysics(space);
          ball->applyImpulse(cpv(mouse_x, mouse_y), cpv(cannon->getX(), cannon->getY()));
        }
      }
    }
    
    // move
    cpSpaceStep(space, 1.0f/ticks_per_sec);
    cpSpaceHashEach(space->activeShapes, &updateShape, NULL);
    gameLoop();
    
    // clear display
    glClear(GL_COLOR_BUFFER_BIT);
    
    // display
    vector<Sprite*>::iterator sprite;
    for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
      if (!draw_physics)
        (*sprite)->display();
      else {
        // drawPhysics(space);
        drawSpaceOptions options = {0,0,1,4.0f,0.0f,1.5f,};
        drawSpace(space, &options);
      }
    }
    
    // update the screen
    SDL_GL_SwapBuffers();
    
    frame++;
    
    // delay to have a consistent framerate
    if (fps.get_ticks() < 1000 / ticks_per_sec) {
      SDL_Delay((1000/ticks_per_sec) - fps.get_ticks());
    }
  }
}

void Scene::setDrawPhysics(bool draw) {
  draw_physics = draw;
}

void Scene::defineBorder(bool top, bool right, bool bottom, bool left) {
  float border_elasticity = 0.3f;
  float border_friction = 1.0f;
  
  // top border
  if (top) {
    cpShape *border_top = cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(320, 0), 0.0f);
    border_top->e = border_elasticity; border_top->u = border_friction;
    cpSpaceAddStaticShape(space, border_top);
  }
  
  // right border
  if (right) {
    cpShape *border_right = cpSegmentShapeNew(staticBody, cpv(320, 0), cpv(320, 480), 0.0f);
    border_right->e = border_elasticity; border_right->u = border_friction;
    cpSpaceAddStaticShape(space, border_right);
  }
  
  // bottom border
  if (bottom) {
    cpShape *border_bottom = cpSegmentShapeNew(staticBody, cpv(0, 480), cpv(320, 480), 0.0f);
    border_bottom->e = border_elasticity; border_bottom->u = border_friction;
    cpSpaceAddStaticShape(space, border_bottom);
  }
  
  // left border
  if (left) {
    cpShape *border_left = cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(0, 480), 0.0f);
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
}

static int ignore_pre_solve(cpArbiter *arb, cpSpace *space, void *ignore) {
  return 0;
}