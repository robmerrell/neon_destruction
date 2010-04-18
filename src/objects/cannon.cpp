#include "cannon.h"

Cannon::Cannon(float x, float y) : Sprite("", 64, 64, CANNON_TAG) {
  setX(x);
  setY(y);
}

void Cannon::definePhysics(cpSpace *space) {
  // body
  cpBody *body = cpBodyNew(30.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // base shape
  cpVect base_verts[] = { cpv(0.0, 0.0), cpv(50.0, 0.0), cpv(50.0, -15.0), cpv(0.0, -15.0) };
  cpShape *baseShape = cpPolyShapeNew(body, 4, base_verts, cpvzero);  
  baseShape->e = 0.5; baseShape->u = 0.9;
  baseShape->data = this;
  baseShape->collision_type = CANNON_COLLISION;
  cpSpaceAddShape(space, baseShape);
}

void Cannon::display() {

}