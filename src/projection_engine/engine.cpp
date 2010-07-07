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
    glRotatef(-270, 0, 0, 1);
    glRotatef(180, 1, 0, 0);
    glScalef(-1.0, -1.0, 1.0);
    glOrthof(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
  #else
    glOrthof(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
  #endif
  
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  
  draw_physics = _draw_physics;
}

Engine::~Engine() {
  TexManager::Instance()->deleteAllTextures();
  SDL_Quit();
}

bool Engine::showScene(Scene *scene) {
  scene->setDrawPhysics(draw_physics);
  bool results = scene->setup();
  
  return results;
}
