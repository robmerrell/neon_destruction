#include "../projection_engine/sprite.h"
#include "../game_const.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public Sprite {

  private:
    cpBody *body;
    float start_x;
    float start_y;
    float end_x;
    float end_y;

  public:
    /**
     * Load the platform onto the scene
     * float start_x
     * float start_y
     * float end_x
     * float end_y
     */
    Platform(float, float, float, float);
    
    /**
     * Define the physics properties of the platform
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the platform
     */
    void display() {}
};

#endif