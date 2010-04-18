#include <map>

#include "SDL.h"
#include "GLES/gl.h"
#include "GLES/glext.h"

#include "scene.h"
#include "sprite.h"
#include "timer.h"

#include "../game_const.h"

#ifndef ENGINE_H
#define ENGINE_H

using namespace std;

class Engine {

  public:
    // constructor
    Engine(bool);
    
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
    
    // if set to true then draw physics shapes instead of applying textures
    bool draw_physics;   
};

#endif