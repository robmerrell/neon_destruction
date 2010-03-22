#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  cannon = new Cannon(100, 100);
  cannon->definePhysics(space);
  addObject(cannon);


  defineBorder(true, true, true, true);
  
  
  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  cpSpaceStep(space, 1.0f/60.0f);
}

