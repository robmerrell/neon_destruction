#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef GRAVITY_SWITCH_H
#define GRAVITY_SWITCH_H

class GravitySwitch : public Sprite {

  private:
    cpBody *body;
    cpShape *switchShape;
    int direction;

  public:
    /**
     * Load the object onto the scene
     * float x
     * float y
     * int direction
     */
    GravitySwitch(float, float, int);
    void destroy(cpSpace*);
    
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