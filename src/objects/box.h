#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef BOX_H
#define BOX_H

class Box : public Sprite {

  private:
    cpBody *body;
    cpShape *boxShape;
    float width;
    float height;
    float mass;
    
    string simulation_type;

  public:
    /**
     * Load the box onto the scene
     * int simulation (STATIC or DYNAMIC)
     */
    Box(string);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the box
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the box
     */
    void display();
    
    /**
     * size
     */
     void setWidth(float);
     void setHeight(float);
     
     void setMass(float);
     
     cpBody* getBody();
};

#endif