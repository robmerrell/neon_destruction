#include "../projection_engine/sprite.h"
#include "../game_const.h"

#ifndef GOAL_H
#define GOAL_H

class Goal : public Sprite {

  private:
    cpBody *body;

  public:
    /**
     * Load the goal onto the scene
     * float x
     * float y
     */
    Goal(float, float);
    
    /**
     * Define the physics properties of the goal
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the goal
     */
    void display() {}
};

#endif