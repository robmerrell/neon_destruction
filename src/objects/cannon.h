#include "../projection_engine/sprite.h"

#ifndef CANNON_H
#define CANNON_H

class Cannon : public Sprite {

  public:
    /**
     * Load the cannon onto the scene
     * float x
     * float y
     */
    Cannon(float, float);
    
    /**
     * Define the physics properties of the cannon
     */
    void definePhysics(cpSpace*);
    
};

#endif