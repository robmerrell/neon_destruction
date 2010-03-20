// stdlib
#include <vector>

// utilities
#include "SDL.h"
#include "SDL_opengl.h"

// engine
#include "sprite.h"
#include "timer.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {

  protected:
    bool in_loop;
    SDL_Event event;
    std::vector<Sprite*> objects;
    
    // frame capping
    int frame;
    Timer fps;
    
    // physics
  
  public:
    /**
     * Constructor
     */
    Scene();
    ~Scene();
    
    /**
     * Handle setup of game objects for the scene in preparation for the game loop
     */
    virtual void setup() {};
    
    /**
     * Add a sprite to the scene
     *
     * Sprite* pointer to a sprite to add
     */
    void addObject(Sprite*);
    
    /**
     * Schedules a loop that calls the param method every count seconds
     *
     * int ticks per second: ex 60
     */
    void scheduleLoop(int);
    
    /**
     * The actual method called in each scene that contains the looping logic
     */
    virtual void gameLoop() {};
};


#endif