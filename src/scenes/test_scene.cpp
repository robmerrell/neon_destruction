#include "test_scene.h"

void TestScene::setup() {
  defineBorder(true, true, true, true);
  
  cannon = new Cannon(30, 300);
  cannon->definePhysics(space);
  addObject(cannon);
  
  Goal *goal = new Goal(400, 225);
  goal->definePhysics(space);
  addObject(goal);
  
  GravitySwitch *gs = new GravitySwitch(100, 100, GRAVITY_UP);
  gs->definePhysics(space);
  addObject(gs);

  Platform *platform1 = new Platform(10, 300, 85, 300);
  platform1->definePhysics(space);
  addObject(platform1);
  
  Platform *platform2 = new Platform(400, 250, 475, 250);
  platform2->definePhysics(space);
  addObject(platform2);
  
  // start the game loop
  scheduleLoop(60);
}


void TestScene::gameLoop() {
  
}