#include "../projection_engine/scene.h"

#include <iostream>

using namespace std;

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

class TitleScene : public Scene {
  
  private:
    bool quit;
    bool loaded;
    bool playing_music;
    
    int frame;
    Timer fps;
    Timer animation;
    float animation_ticks;
    
  public:
    TitleScene();
    ~TitleScene();
    
    bool setup();
    void gameLoop();
};

#endif