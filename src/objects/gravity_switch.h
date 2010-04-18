#include "../projection_engine/sprite.h"
#include "../game_const.h"

#ifndef GRAVITY_SWITCH_H
#define GRAVITY_SWITCH_H

class GravitySwitch : public Sprite {

  private:
    cpBody *body;
    int direction;

  public:
    /**
     * Load the object onto the scene
     * float x
     * float y
     * int direction
     */
    GravitySwitch(float, float, int);
    
    /**
     * Define the physics properties of the object
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the gravity switch
     */
    void display();
    
    /**
     * Get the direction
     */
    int getDirection();
};

#endif