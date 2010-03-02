#include "engine.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

Engine::Engine() {
  // create the sdl context
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  
}

Engine::~Engine() {
  SDL_Quit();
}


void Engine::loop() {
  in_loop = true;
  
  while (in_loop) {
    while (SDL_PollEvent(&event)) {
      
      // the window was closed
      if (event.type == SDL_QUIT) {
        in_loop = false;
      }
      
      // apply force if the mouse was clicked
      
      
      // redraw the scene
      
      
    }
  }
}


bool Engine::showScene() {
  return true;
}