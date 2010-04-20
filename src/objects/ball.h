#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef BALL_H
#define BALL_H

class Ball : public Sprite {

  private:
    cpBody *body;

  public:
    /**
     * Load the ball onto the scene
     * float x
     * float y
     */
    Ball(float, float);
    
    /**
     * Define the physics properties of the ball
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the ball
     */
    void display();
    
    /**
     * Apply an impulse to the ball
     *
     * cpv(mouse coords), cpv(originating coords)
     */
    void applyImpulse(cpVect, cpVect);
};

#endif