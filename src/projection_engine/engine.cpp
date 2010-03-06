#include "engine.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

Engine::Engine() {
  // create the sdl context
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
  
  // setup openGL
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
  
  // setup the modelview matrix for our sprites
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

Engine::~Engine() {
  SDL_Quit();
}

bool Engine::showScene(Scene *scene) {
  scene->setup();
  
  return true;
}