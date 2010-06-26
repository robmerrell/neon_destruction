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
    
    int current_level;
    bool quit;
    
    // frame capping
    int frame;
    Timer fps;
    float animation_ticks;
    
    cpVect starfield1[STARS_PER_FIELD];
    cpVect starfield2[STARS_PER_FIELD];
    
    float starfield_colors[(STARS_PER_FIELD * 2) * 4];
    float starfield_sizes[STARS_PER_FIELD * 2];
    
    // physics
    cpSpace *space;
    cpBody *staticBody;
  
  public:
    GameplayScene();
    ~GameplayScene();
    
    static bool finished_level;
    
    void setup();
    void gameLoop();
    void loadLevel(string);
    void replaceLevel(string);
    
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
    
    /**
     * Add static shape segment borders to the scene.
     * The arguments go in order of top, right, bottom, left
     */
    void defineBorder(bool, bool, bool, bool);
};

void updateShape(void*, void*);
static int ignore_pre_solve(cpArbiter*, cpSpace*, void*);
static int pre_solve_goal(cpArbiter*, cpSpace*, void*);
static int gravity_switch_solver(cpArbiter*, cpSpace*, void*);

#endif