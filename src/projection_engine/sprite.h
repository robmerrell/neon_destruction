#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
  
  protected:
    float x;
    float y;
    
    float width;
    float height;
    
    
  public:
    /**
     * Constructor
     *
     * string file name of the image
     */
     Sprite(std::string);
     
    /**
     * Define the sprite's display properties through openGL
     */
    void display();

    /**
     * Getters and setters for position
     */
     float getX();
     void setX(float);
     float getY();
     void setY(float);
     
    /**
     * Getters for the size
     */
     float getWidth();
     float getHeight();
};

#endif