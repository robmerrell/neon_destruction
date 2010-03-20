#include "scene.h"

using namespace std;

Scene::Scene() {
  in_loop = false;
  frame = 0;
}

// TODO: check this for memory leaks
Scene::~Scene() {
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
      (*sprite)->display();
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