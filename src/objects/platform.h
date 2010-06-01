#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public Sprite {

  private:
    cpBody *body;
    
    float width;
    float height;

  public:
    /**
     * Load the platform onto the scene
     * string type
     */
    Platform(string);
    
    /**
     * Define the physics properties of the platform
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the platform
     */
    void display();
};

#endif