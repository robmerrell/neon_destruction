#include "intro_scene.h"

void IntroScene::setup() {
  defineBorder(true, true, true, true);
  
  cannon = new Cannon(100, 100);
  cannon->definePhysics(space);
  addObject(cannon);
  
  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  
}

