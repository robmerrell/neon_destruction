#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef CANNON_H
#define CANNON_H

class Cannon : public Sprite {

  private:
    cpBody *body;
    float turret_angle;

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
    
    /**
     * Display the cannon
     */
    void display();
    
    /**
     * Rotate the turet
     * float angle
     */
    void rotateTurret(float);
    
};

#endif