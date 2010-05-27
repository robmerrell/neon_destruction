#include "gameplay_scene.h"

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  Box *box = new Box(BOX_TALL_SKINNY, SIMULATION_STATIC);
  box->setX(100.0f);
  box->setY(100.0f);
  box->setAngle(30.0f);
  box->definePhysics(space);
  addObject(box);
  
  /*
  Cannon *cannon = new Cannon(20.0f, 276.0f);
  cannon->definePhysics(space);
  addObject(cannon);
  
  Box *base = new Box(200, 270, 100, 100);
  base->definePhysics(space);
  addObject(base);
  
  Box *middle = new Box(220, 190, 60, 60);
  middle->definePhysics(space);
  addObject(middle);
  
  Box *middle_smaller = new Box(230, 85, 20, 150);
  middle_smaller->definePhysics(space);
  addObject(middle_smaller);
  
  Platform *platform = new Platform(400, 100, 480, 100);
  platform->definePhysics(space);
  addObject(platform);
  */
  
  // start the game loop
  scheduleLoop(60);
}