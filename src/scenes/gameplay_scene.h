#include "../projection_engine/scene.h"
#include "../tinyxml/tinyxml.h"

#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

class GameplayScene : public Scene {
  
  private:
    bool has_cannon;
  
  public:
    GameplayScene() {};
    
    void setup();
    void gameLoop() {};
};

#endif