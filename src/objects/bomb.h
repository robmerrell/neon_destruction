#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "ball.h"
#include "SDL.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb : public Sprite {

  private:
    cpBody *body;
    cpShape *bombShape;
    int force;
    float elasticity;
    float mass;
    bool exploding;
    bool destroyed;
    bool destroyed_physics;
    bool destroyed_sprite;
    string simulation_type;
    
    Particle **particles;
    
  public:
    /**
     * Load the bomb onto the scene
     * string physics simulation type
     */
    Bomb(string);
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the circle
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the circle
     */
    void display();
    
    void setElasticity(float);
    void setMass(float);
    void setForce(int);
    int getForce();
    
    void explode(int);
    
    void manageParticles(int, int, cpSpace*);
};

#endif
