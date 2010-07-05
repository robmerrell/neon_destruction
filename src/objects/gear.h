#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef GEAR_H
#define GEAR_H

class Gear : public Sprite {

  private:
    cpBody *body;
    cpBody *pbody;
    cpShape *platformShape;
    cpShape *platformShape2;
    
    float width;
    float height;
    float physics_height;

  public:
    /**
     * Load the gear onto the scene
     */
    Gear();
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the platform
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the platform
     */
    void display();
    
    /**
     * Size
     */
    void setWidth(float);
    
    /**
     * Apply an impulse to the body at coordinates
     */
    void applyImpulse(float, float);
};

#endif