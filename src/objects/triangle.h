#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle : public Sprite {

  private:
    cpBody *body;
    cpShape *triangleShape;
    float width;
    float height;
    
    string simulation_type;

  public:
    /**
     * Load the triangle onto the scene
     * int simulation (STATIC or DYNAMIC)
     */
    Triangle(string);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the triangle
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the triangle
     */
    void display();
    
    /**
     * size
     */
     void setWidth(float);
     void setHeight(float);
};

#endif