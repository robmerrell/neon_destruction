#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"

#ifndef TEXTURE_STRING_H
#define TEXTURE_STRING_H

class TextureString : public Sprite {

  private:
    string message;
    float r;
    float g;
    float b;

  public:
    /**
     * Load the object onto the scene
     * float x
     * float y
     */
    TextureString(float, float, string);
    
    void setMessage(string);
    
    void color(float, float, float);
    
    /**
     * Define the physics properties of the object
     */
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the string
     */
    void display();
};


const cpVect FONTMAP[] = {
  cpv(187, 0),
  cpv(198, 0),
  cpv(209, 0),
  cpv(220, 0),
  cpv(231, 0),
  cpv(242, 0),
  cpv(0, 18),
  cpv(11, 18),
  cpv(22, 18),
  cpv(33, 18),
  cpv(44, 18),
  cpv(55, 18),
  cpv(66, 18),
  cpv(77, 18),
  cpv(88, 18),
  cpv(99, 18),
  cpv(110, 18),
  cpv(121, 18),
  cpv(132, 18),
  cpv(143, 18),
  cpv(154, 18),
  cpv(165, 18),
  cpv(176, 18),
  cpv(187, 18),
  cpv(198, 18),
  cpv(209, 18),
  cpv(220, 18),
  cpv(231, 18),
  cpv(242, 18),
  cpv(0, 36),
  cpv(11, 36),
  cpv(22, 36),
  cpv(33, 36),
  cpv(44, 36),
  cpv(55, 36),
  cpv(66, 36),
  cpv(77, 36),
  cpv(88, 36),
  cpv(99, 36),
  cpv(110, 36),
  cpv(121, 36),
  cpv(132, 36),
  cpv(143, 36),
  cpv(154, 36),
  cpv(165, 36),
  cpv(176, 36),
  cpv(187, 36),
  cpv(198, 36),
  cpv(209, 36),
  cpv(220, 36),
  cpv(231, 36),
  cpv(242, 36),
  cpv(0, 54),
  cpv(11, 54),
  cpv(22, 54),
  cpv(33, 54),
  cpv(44, 54),
  cpv(55, 54),
  cpv(66, 54),
  cpv(77, 54),
  cpv(88, 54),
  cpv(99, 54),
  cpv(110, 54),
  cpv(121, 54),
  cpv(132, 54),
  cpv(143, 54),
  cpv(154, 54),
  cpv(165, 54),
  cpv(176, 54),
  cpv(187, 54),
  cpv(198, 54),
  cpv(209, 54),
  cpv(220, 54),
  cpv(231, 54),
  cpv(242, 54),
  cpv(0, 72),
  cpv(11, 72),
  cpv(22, 72),
  cpv(33, 72),
  cpv(44, 72),
  cpv(55, 72),
  cpv(66, 72),
  cpv(77, 72),
  cpv(88, 72),
  cpv(99, 72),
  cpv(110, 72),
  cpv(121, 72),
  cpv(132, 72),
  cpv(143, 72),
  cpv(154, 72),
  cpv(165, 72),
  cpv(176, 72),
  cpv(187, 72),
  cpv(198, 72),
  cpv(209, 72) 
};

#endif