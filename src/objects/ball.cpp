#include "ball.h"
#include <iostream>
#include <Math.h>

using namespace std;

Ball::Ball(float x, float y) : Sprite("", 64, 64, BALL_TAG) {
  setX(x);
  setY(y);
}

void Ball::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(1.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // ball shape
  cpShape *ballShape = cpCircleShapeNew(body, 10.0, cpvzero);
  ballShape->e = 0.8;
  ballShape->u = 0.2;
  ballShape->data = this;
  ballShape->collision_type = BALL_COLLISION;
  cpSpaceAddShape(space, ballShape);
}

void Ball::applyImpulse(cpVect mouse, cpVect originating) {
  float delta_x, delta_y, vect_x, vect_y;
  bool negate;
  
  // get dx and dy
  delta_x = mouse.x - originating.x;
  if (mouse.y < originating.y) {
    delta_y = originating.y - mouse.y;
    negate = true;
  } else {
    delta_y = mouse.y - originating.y;
    negate = false;
  }
  
  // figure out our impulse vector
  vect_y = sqrt(2 * GRAVITY_RATE * delta_y);
  vect_x = (delta_x * GRAVITY_RATE) / vect_y;
  
  // Because we are using a TL coordinate system we need
  // to invert our y vector when shooting up
  if (negate)
    vect_y = vect_y * -1;
    
  // only allow our x vector to be so fast
  if (vect_x > 650)
    vect_x = 650;
  if (vect_x < -650)
    vect_x = -650;
  
  cout << "delta: " << delta_x << "," << delta_y << endl;
  cout << "vector: " << vect_x << "," << vect_y << endl;
    
  cpBodyApplyImpulse(body, cpv(vect_x, vect_y), cpvzero);
}