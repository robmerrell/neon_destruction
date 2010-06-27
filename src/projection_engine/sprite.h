#include <iostream>
#include "game_object.h"
#include "../game_const.h"
#include "GLES/gl.h"

#include "../chipmunk/headers/chipmunk.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public GameObject {
  
  protected:
    float width;
    float height;
    float angle;
    int tag;
    int animation_state;
    
  public:
    /**
     * Constructor
     *
     * string file name of the image
     * float width
     * float height
     * int tag
     */
    Sprite(std::string, float, float, int);

    /**
     * Getters for the size and the tag
     */
    float getWidth();
    float getHeight();
    float getAngle();
    void setAngle(float);
    int getTag();
    
    void setAnimationState(int);
    int getAnimationState();
    
    virtual void definePhysics(cpSpace*) {};
    virtual void destroy(cpSpace*) {};
    virtual void emitParticles(int) {};
    virtual void manageParticles(int, int) {};
};

#endif