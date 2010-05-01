#include "test_scene.h"

void TestScene::setup() {
  defineBorder(true, true, true, true);
  defineBackground(2);
  
  cannon = new Cannon(140, 106);
  cannon->definePhysics(space);
  addObject(cannon);

  Goal *goal = new Goal(400, 225);
  goal->definePhysics(space);
  addObject(goal);
  
  /*
  GravitySwitch *gs = new GravitySwitch(100, 100, GRAVITY_UP);
  gs->definePhysics(space);
  addObject(gs);
  */

  Platform *platform1 = new Platform(155, 150, 180, 150);
  platform1->definePhysics(space);
  addObject(platform1);
  
  Platform *platform2 = new Platform(400, 250, 475, 250);
  platform2->definePhysics(space);
  addObject(platform2);
  
  Platform *platform3 = new Platform(50, 150, 200, 250);
  platform3->definePhysics(space);
  addObject(platform3);

  Platform *platform4 = new Platform(250, 15, 250, 200);
  platform4->definePhysics(space);
  addObject(platform4);
  
  Box *box = new Box(50, 150, 40, 40);
  box->definePhysics(space);
  addObject(box);
  
  // start the game loop
  scheduleLoop(60);
}


void TestScene::gameLoop() {
  
}