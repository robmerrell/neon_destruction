#include "../projection_engine/scene.h"
#include "../objects/cannon.h"

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

class TestScene : public Scene {
  
  private:
    Cannon *cannon;
  
  public:
    TestScene() {};
    
    void setup();
    void gameLoop();
  
};

#endif