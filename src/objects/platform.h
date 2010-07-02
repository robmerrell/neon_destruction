#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public Sprite {

  private:
    cpBody *body;
    cpShape *platformShape;
    
    float width;
    float height;
    float physics_height;
    
    string simulation_type;

  public:
    /**
     * Load the platform onto the scene
     */
    Platform(string);
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
};

#endif