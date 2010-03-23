#include "ball.h"

Ball::Ball(float x, float y) : Sprite("", 64, 64, BALL_TAG) {
  setX(x);
  setY(y);
}

void Ball::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(20.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // ball shape
  cpShape *ballShape = cpCircleShapeNew(body, 10.0, cpvzero);
  ballShape->e = 0.5;
  ballShape->u = 0.3;
  ballShape->data = this;
  ballShape->collision_type = BALL_COLLISION;
  cpSpaceAddShape(space, ballShape);
}

void Ball::applyImpulse(cpVect mouse, cpVect originating) {
  // find the distance
  float delta_y = mouse.y - originating.y;
  float delta_x = mouse.x - originating.x;

  // apply the impulse
  cpBodyApplyImpulse(body, cpv(delta_x * PROJECTION_MULTIPLIER, delta_y * PROJECTION_MULTIPLIER), cpvzero);
}