#include "engine.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

Engine::Engine(bool _draw_physics) {
  // create the sdl context
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
  
  // setup openGL
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
  
  // blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  
  // setup the modelview matrix for our sprites
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glEnableClientState(GL_VERTEX_ARRAY);
  
  draw_physics = _draw_physics;
}

Engine::~Engine() {
  SDL_Quit();
}

bool Engine::showScene(Scene *scene) {
  scene->setDrawPhysics(draw_physics);
  scene->setup();
  
  return true;
}