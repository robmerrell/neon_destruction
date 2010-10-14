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
    bool moves;
    int tag;
    int animation_state;
    std::string id;
    
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
    void setTag(int);
    void setId(std::string);
    std::string getId();
    
    bool moveable();
    
    void setAnimationState(int);
    int getAnimationState();

    virtual cpBody* getBody() {};
    
    virtual void definePhysics(cpSpace*) {};
    virtual void destroy(cpSpace*) {};
    virtual void emitParticles(int) {};
    virtual void manageParticles(int, int) {};
    virtual void manageParticles(int, int, cpSpace*) {};
    virtual void move(int) {};
    virtual void setMessage(std::string) {};
    virtual void color(float, float, float) {};
};

#endif