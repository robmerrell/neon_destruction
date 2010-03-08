#include "SDL.h"
#include "SDL_opengl.h"

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
  
  protected:
    float x;
    float y;
    
  public:
    /**
     * Constructor
     */
    GameObject() {};
     
    /**
     * openGL display routine
     */
    virtual void display() {};

    /**
     * Getters and setters for position
     */
    float getX();
    void setX(float);
    float getY();
    void setY(float);

};

#endif