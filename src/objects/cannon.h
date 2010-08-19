#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef CANNON_H
#define CANNON_H

class Cannon : public Sprite {

  private:
    cpBody *body;
    float turret_angle;
    string orientation;

  public:
    /**
     * Load the cannon onto the scene
     * float x
     * float y
     */
    Cannon(float, float);
    
    /**
     * Define the physics properties of the cannon
     */
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the cannon
     */
    void display();
    
    /**
     * Rotate the turet
     * float angle
     */
    void rotateTurret(float);
    
    /**
     * Set the orientation for the bannon base
     * string N,S,E,W
     */
    void setOrientation(string);
    
    /**
     * Return the coordinates that have been translated along with the textures
     */
    cpVect translatedCoords();
    
};

#endif