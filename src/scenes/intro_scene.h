#include "../projection_engine/scene.h"

#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H

class IntroScene : public Scene {
  
  private:
    Sprite* logo;
    b2AABB worldAABB;
    b2World* world;
    b2Body* body;
  
  public:
    IntroScene() {};
    
    /**
     * Setup the logo sprite
     */
    void setup();
    
    /**
     * Main game loop for the scene.  Shows the logo image and fades it out
     */
    void gameLoop();
  
};

#endif