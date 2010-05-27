#include "box_tumble.h"

void BoxTumble::setup() {
  defineBorder(true, true, true, true);
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
/*  
  cannon = new Cannon(140, 106);
  cannon->definePhysics(space);
  addObject(cannon);

  Goal *goal = new Goal(400, 225);
  goal->definePhysics(space);
  addObject(goal);
  
  GravitySwitch *gs = new GravitySwitch(100, 100, GRAVITY_UP);
  gs->definePhysics(space);
  addObject(gs);

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
  */
  
  // start the game loop
  scheduleLoop(60);
}