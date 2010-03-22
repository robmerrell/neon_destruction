#include <iostream>
#include "game_object.h"

#include "chipmunk/chipmunk.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public GameObject {
  
  protected:
    float width;
    float height;
    
  public:
    /**
     * Constructor
     *
     * string file name of the image
     * float width
     * float height
     */
    Sprite(std::string, float, float);
     
     /**
      * Render a texture to a square made of a triangle stip
      */
     void display();

    /**
     * Getters for the size
     */
    float getWidth();
    float getHeight();
    
    virtual void definePhysics(cpSpace*) {};
};

#endif