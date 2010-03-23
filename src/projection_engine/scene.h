// stdlib
#include <vector>

// utilities
#include "SDL.h"
#include "SDL_opengl.h"
#include "chipmunk/chipmunk.h"
#include "chipmunk/drawSpace.h"

#include "../game_const.h"
#include "../objects/ball.h"

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
    cpSpace *space;
    cpBody *staticBody;
    bool draw_physics;
  
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
     * Find an object in the scene based on the tag
     *
     * int tag
     */
    Sprite* findObject(int);
    
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
    
    /**
     * Propagated from the engine, tell the scene that we should render physics and not textures
     */
    void setDrawPhysics(bool);
    
    /**
     * Add static shape segment borders to the scene.
     * The arguments go in order of top, right, bottom, left
     */
    void defineBorder(bool, bool, bool, bool);
};

void updateShape(void*, void*);

static int ignore_pre_solve(cpArbiter*, cpSpace*, void*);

#endif