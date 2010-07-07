#include "../projection_engine/scene.h"

#include <iostream>

using namespace std;

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

class TitleScene : public Scene {
  
  private:
    bool quit;
    
    int frame;
    Timer fps;
    Timer animation;
    float animation_ticks;
    
    cpVect starfield1[STARS_PER_FIELD];
    cpVect starfield2[STARS_PER_FIELD];
    
    float starfield_colors[(STARS_PER_FIELD * 2) * 4];
    float starfield_sizes[STARS_PER_FIELD * 2];
    
  public:
    TitleScene();
    ~TitleScene();
    
    bool setup();
    void gameLoop();
    
    /**
     * Defines the colors used for the star background
     */
    void defineStarColors();
    
    /**
     * Add the level background to a scene
     */
    void drawBackground();
    
    /**
     * Moves the star fields
     */
    void moveBackground(int);
};

#endif