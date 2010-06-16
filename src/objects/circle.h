#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Sprite {

  private:
    cpBody *body;
    float radius;

  public:
    /**
     * Load the circle onto the scene
     * string physics simulation type
     */
    Circle(string);
    
    /**
     * Define the physics properties of the circle
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the circle
     */
    void display();
    
    void setRadius(float);
};

#endif