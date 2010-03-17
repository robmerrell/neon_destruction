#include "scene.h"

using namespace std;

Scene::Scene() {
  in_loop = false;
  frame = 0;
  
  // setup the physics environment
  worldAABB.lowerBound.Set(0, 0);
  worldAABB.upperBound.Set(640/PTM_RATIO, 480/PTM_RATIO);
  
  b2Vec2 gravity(0.0f, 10.0f);
  bool doSleep = true;
  
  world = new b2World(worldAABB, gravity, doSleep);
}

// TODO: check this for memory leaks
Scene::~Scene() {
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
  
  delete world;
  world = NULL;
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
    
    // physics step
    float32 timeStep = 1.0f / ticks_per_sec;
    int32 iterations = 10;
    world->Step(timeStep, iterations);
    
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


float Scene::p2m(float pixel) {
  return pixel / PTM_RATIO;
}

float Scene::m2p(float meters) {
  return meters * PTM_RATIO;
}