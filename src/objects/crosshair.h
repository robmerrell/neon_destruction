#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef CROSS_HAIR_H
#define CROSS_HAIR_H

class CrossHair : public Sprite {

  private:
    cpBody *body;

  public:
    /**
     * Load the object onto the scene
     * float x
     * float y
     */
    CrossHair(float, float);
    
    /**
     * Define the physics properties of the object
     */
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the cross hairs
     */
    void display();
};

#endif