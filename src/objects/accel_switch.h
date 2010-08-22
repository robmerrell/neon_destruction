#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef ACCEL_SWITCH_H
#define ACCEL_SWITCH_H

class AccelSwitch : public Sprite {

  private:
    cpBody *body;
    cpShape *switchShape;
    int direction;
    
    bool should_block;

  public:
    /**
     * Load the object onto the scene
     * float x
     * float y
     */
    AccelSwitch(float, float);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the object
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the accel switch
     */
    void display();
    
    void block();
};

#endif