#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Sprite {

  private:
    cpBody *body;
    cpShape *circleShape;
    float radius;
    float elasticity;
    float mass;
    
    bool egg;

    string simulation_type;
  public:
    /**
     * Load the circle onto the scene
     * string physics simulation type
     */
    Circle(string);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the circle
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the circle
     */
    void display();
    
    void setRadius(float);
    void setElasticity(float);
    void setMass(float);
    
    void eColl();
    
    cpBody* getBody();
};

#endif