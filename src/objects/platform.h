#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public Sprite {

  private:
    cpBody *body;
    cpBody *pbody;
    cpShape *platformShape;

    float mass;
    float width;
    float height;
    float physics_height;
    bool fixed;
    
    string simulation_type;
    string id;

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
    
    /**
     * Apply an impulse to the body at coordinates
     */
    void applyImpulse(float, float);
    
    /**
     * Fix the platform in place with a pivot joint
     */
    void fix(cpSpace*);
    
    void setId(string);
    string getId();
    
    void setMass(float);
    
    cpBody* getBody();
};

#endif