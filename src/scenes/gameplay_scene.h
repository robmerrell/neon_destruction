#include "../projection_engine/scene.h"
#include "../tinyxml/tinyxml.h"

#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

class GameplayScene : public Scene {
  
  public:
    GameplayScene() {};
    
    void setup();
    void gameLoop() {};
};

#endif