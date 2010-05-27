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
    
    int box_type;
    int simulation_type;

  public:
    /**
     * Load the box onto the scene
     * int box type
     * int simulation (STATIC or DYNAMIC)
     */
    Box(int, int);
    
    /**
     * Load the box onto the scene
     * float x
     * float y
     * float width
     * float height
     */
    Box(float, float, float, float);
    
    /**
     * Define the physics properties of the box
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the box
     */
    void display();
};

#endif