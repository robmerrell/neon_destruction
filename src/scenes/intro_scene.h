#include "../projection_engine/scene.h"

#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H

class IntroScene : public Scene {
  
  public:
    IntroScene();
    
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