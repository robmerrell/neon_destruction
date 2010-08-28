#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef GOAL_H
#define GOAL_H

class Goal : public Sprite {

  private:
    cpBody *body;
    cpShape *goalShape;
    float mass;

  public:
    /**
     * Load the goal onto the scene
     * float x
     * float y
     */
    Goal(float, float);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the goal
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the goal
     */
    void display();
    
    cpBody* getBody();
    void setMass(float);
};

#endif