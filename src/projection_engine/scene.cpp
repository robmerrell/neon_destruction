#include "scene.h"

using namespace std;

Scene::Scene() {
  in_loop = false;
}

// TODO: check this for memory leaks
Scene::~Scene() {
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    delete (*iter);
  }

  objects.clear();
}

void Scene::addObject(Sprite* sprite) {
  objects.push_back(sprite);
}

void Scene::scheduleLoop(float ticks_per_sec) {
  in_loop = true;
  
  while (in_loop) {
    
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
      (*sprite)->display();
    }
    
    // update the screen
    SDL_GL_SwapBuffers();
    
    // delay to have a consistent framerate
  }
}