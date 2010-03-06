#include "SDL.h"
#include "SDL_opengl.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {

  protected:
    bool in_loop;
    SDL_Event event;
  
  public:
    /**
     * Constructor
     */
    Scene();
    
    /**
     * Handle setup of game objects for the scene in preparation for the game loop
     */
   virtual void setup() {};
    
    /**
     * Schedules a loop that calls the param method every count seconds
     *
     * float ticks per second: ex 1.0f/60.f
     */
    void scheduleLoop(float);
    
    /**
     * The actual method called in each scene that contains the looping logic
     */
    virtual void gameLoop() {};
  
};

#endif