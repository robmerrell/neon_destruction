#include "../projection_engine/scene.h"

#include <iostream>

using namespace std;

#ifndef THANK_YOU_SCENE_H
#define THANK_YOU_SCENE_H

class ThankYouScene : public Scene {
  
  private:
    bool quit;
    
    int frame;
    Timer fps;
    Timer animation;
    float animation_ticks;
    
  public:
    ThankYouScene();
    ~ThankYouScene();
    
    bool setup();
    void gameLoop();
};

#endif