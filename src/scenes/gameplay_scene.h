#include "../projection_engine/scene.h"
#include "../tinyxml/tinyxml.h"

#include <iostream>

using namespace std;

#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

class GameplayScene : public Scene {
  
  private:
    bool has_cannon;
    bool has_goal;
  
  public:
    GameplayScene() {};
    
    void setup();
    void gameLoop() {};
    void loadLevel(string);
    void replaceLevel(string);
};

#endif