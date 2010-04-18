#include "gravity_switch.h"

GravitySwitch::GravitySwitch(float x, float y, int _direction) : Sprite("", 64, 64, GRAVITY_SWITCH_TAG) {
  direction = _direction;
  
  setX(x);
  setY(y);
}

void GravitySwitch::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);

  // goal shape
  cpShape *goalShape = cpCircleShapeNew(body, 15.0, cpvzero);
  goalShape->e = 0.5;
  goalShape->u = 0.3;
  goalShape->data = this;
  goalShape->collision_type = GRAVITY_SWITCH_COLLISION;
  cpSpaceAddStaticShape(space, goalShape);
}

int GravitySwitch::getDirection() {
  return direction;
}

void GravitySwitch::display() {
  
}