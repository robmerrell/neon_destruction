// stdlib
#include <vector>
#include <Math.h>

// utilities
#include "SDL.h"
#include "GLES/gl.h"
#include "../chipmunk/headers/chipmunk.h"
#include "event_translations.h"

#include "draw_physics.h"
#include "../game_const.h"
#include "../objects/goal.h"
#include "../objects/ball.h"
#include "../objects/platform.h"
#include "../objects/gravity_switch.h"
#include "../objects/cannon.h"
#include "../objects/box.h"
#include "../objects/crosshair.h"
#include "../objects/circle.h"
#include "../objects/triangle.h"
#include "../objects/gear.h"

// engine
#include "sprite.h"
#include "timer.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {

  protected:
    int score;
    bool in_loop;
    SDL_Event event;
    std::vector<Sprite*> objects;
    
    bool draw_physics;
  
  public:
    /**
     * Constructor
     */
    Scene() {};
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
     * The actual method called in each scene that contains the looping logic
     */
    virtual void gameLoop() {};
    
    /**
     * Propagated from the engine, tell the scene that we should render physics and not textures
     */
    void setDrawPhysics(bool);
    
    /**
     * Update the animation for all objects
     */
    void updateAnimation(int);
};


#endif