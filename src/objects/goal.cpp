#include "goal.h"

Goal::Goal(float x, float y) : Sprite("", 64, 64, GOAL_TAG) {
  setX(x);
  setY(y);
}

void Goal::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(20.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // goal shape
  cpShape *goalShape = cpCircleShapeNew(body, 20.0, cpvzero);
  goalShape->e = 0.5;
  goalShape->u = 0.3;
  goalShape->data = this;
  goalShape->collision_type = GOAL_COLLISION;
  cpSpaceAddShape(space, goalShape);
}