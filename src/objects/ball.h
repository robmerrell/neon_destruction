#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef BALL_H
#define BALL_H

struct Particle {
  float x;
  float y;
  int birth;
  float direction;
  int color;
  bool dead;
};

static GLfloat colors[12][3]=
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

class Ball : public Sprite {

  private:
    cpBody *body;
    cpShape *ballShape;
    
    Particle **particles;
    
    float last_particle_x;
    float last_particle_y;

  public:
    /**
     * Load the ball onto the scene
     * float x
     * float y
     */
    Ball(float, float);
    ~Ball();
    void destroy(cpSpace*);
    
    /**
     * Define the physics properties of the ball
     */
    void definePhysics(cpSpace*);
    
    /**
     * Display the ball
     */
    void display();
    
    /**
     * Apply an impulse to the ball
     *
     * cpv(mouse coords), cpv(originating coords)
     */
    void applyImpulse(cpVect, cpVect);

    /**
     * Emit a burst of particles
     *
     * int timestep birth
     */
    void emitParticles(int);
    
    /**
     * Clean up and move particles
     *
     * int current timestemp
     * int delta timestep
     */
    void manageParticles(int, int);
};

#endif