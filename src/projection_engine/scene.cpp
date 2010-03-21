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
  // cpSpaceResizeStaticHash(space, 30.0f, 1000);
  // cpSpaceResizeActiveHash(space, 30.0f, 1000);
	space->gravity = cpv(0, 100);
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

void Scene::scheduleLoop(int ticks_per_sec) {
  in_loop = true;
    
  while (in_loop) {
    fps.start();
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
    }
    
    // move
    gameLoop();
    
    // clear display
    glClear(GL_COLOR_BUFFER_BIT);
    
    // display
    vector<Sprite*>::iterator sprite;
    for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
      if (!draw_physics)
        (*sprite)->display();
      else {
        drawPhysics(space);
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