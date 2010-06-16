#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef BOX_H
#define BOX_H

class Box : public Sprite {

  private:
    cpBody *body;
    float width;
    float height;
    
    string simulation_type;

  public:
    /**
     * Load the box onto the scene
     * int simulation (STATIC or DYNAMIC)
     */
    Box(string);
    
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
};

#endif