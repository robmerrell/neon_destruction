#include "SDL.h"
#include "SDL_opengl.h"

#include "scene.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {

  public:
    // constructor
    Engine();
    
    // destructor
    ~Engine();
    
    // main game loop
    void loop();
    
    // replace the current scene with a new scene
    bool showScene(Scene*);
  
  
  private:
    // tracks if we are running in the loop or not
    bool in_loop;
    
    // main display surface
    SDL_Surface* screen;
    
    // SDL event structure
    SDL_Event event;
};

#endif