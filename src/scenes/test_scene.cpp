#include "test_scene.h"

void TestScene::setup() {
  defineBorder(true, true, true, true);
  
  cannon = new Cannon(100, 100);
  cannon->definePhysics(space);
  addObject(cannon);
  
  // start the game loop
  scheduleLoop(60);
}


void TestScene::gameLoop() {
  
}