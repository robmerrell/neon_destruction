#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image : public Sprite {

  private:
    int texture_num;

  public:
    /**
     * Load the image onto the scene
     * float x
     * float y
     */
    Image(float, float, float, float, int);
    
    /**
     * Define the physics properties of the cannon
     */
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the cannon
     */
    void display();
};

#endif