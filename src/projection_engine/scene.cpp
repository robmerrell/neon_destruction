#include "scene.h"

Scene::Scene() {
  in_loop = false;
}

void Scene::scheduleLoop(float ticks_per_sec) {
  in_loop = true;
  
  while (in_loop) {
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        in_loop = false;
    }
    
    // for each tick call the scheduled method
    gameLoop();
    
    // delay to have a consistent framerate
  }
}