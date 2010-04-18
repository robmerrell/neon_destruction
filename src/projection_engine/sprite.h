#include <iostream>
#include "game_object.h"
#include "GLES/gl.h"

#include "../chipmunk/headers/chipmunk.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public GameObject {
  
  protected:
    float width;
    float height;
    int tag;
    
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
      * Render a texture to a square made of a triangle stip
      */
     virtual void display() {};

    /**
     * Getters for the size and the tag
     */
    float getWidth();
    float getHeight();
    int getTag();
    
    virtual void definePhysics(cpSpace*) {};
};

#endif