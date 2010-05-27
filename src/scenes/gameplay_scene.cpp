#include "gameplay_scene.h"

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  Box *box = new Box(BOX_TALL_SKINNY, SIMULATION_STATIC);
  box->setX(100.0f);
  box->setY(100.0f);
  box->setAngle(60.0f);
  box->definePhysics(space);
  addObject(box);
  
  Box *box2 = new Box(BOX_TALL_MEDIUM, SIMULATION_STATIC);
  box2->setX(230.0f);
  box2->setY(100.0f);
  box2->setAngle(60.0f);
  box2->definePhysics(space);
  addObject(box2);
  
  Box *box3 = new Box(BOX_TALL_WIDE, SIMULATION_STATIC);
  box3->setX(400.0f);
  box3->setY(100.0f);
  box3->setAngle(60.0f);
  box3->definePhysics(space);
  addObject(box3);
  
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