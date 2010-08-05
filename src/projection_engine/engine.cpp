#include "engine.h"
#include <stdio.h>

Engine::Engine(bool _draw_physics) {
  // create the sdl context
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  
  #ifdef DEVICE
    screen = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL);
  #else
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
  #endif
  
  // setup openGL
  glClearColor(0, 0, 0, 1.0f);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  #ifdef DEVICE
    glRotatef(-90, 0, 0, 1);
  #endif
  
  glOrthof(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
  
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  
  draw_physics = _draw_physics;
}

Engine::~Engine() {
  TexManager::Instance()->deleteAllTextures();
  SoundManager::Instance()->destroyRefs();
  SDL_Quit();
}

bool Engine::showScene(Scene *scene) {
  scene->setDrawPhysics(draw_physics);
  bool results = scene->setup();
  
  return results;
}
