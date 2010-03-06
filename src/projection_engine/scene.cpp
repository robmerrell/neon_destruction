#include "scene.h"

Scene::Scene() {
  in_loop = false;
}

void Scene::scheduleLoop() {
  in_loop = true;
  
  while (in_loop) {
    // for each tick call the scheduled method
    
    // delay to have a consistent framerate
  }
}