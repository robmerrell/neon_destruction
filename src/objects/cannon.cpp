#include "cannon.h"

Cannon::Cannon(float x, float y) : Sprite("", 64, 64, CANNON_TAG) {
  setX(x);
  setY(y);
}

void Cannon::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(10.0f, INFINITY);
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
  GLfloat shadow_vertices[] = {0,128,0, 128,128,0, 0,0,0, 128,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  // ball shadow
  TexManager::Instance()->bindTexture(3);
  
  glLoadIdentity();
  glTranslatef(body->p.x - 64, body->p.y - 64, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, shadow_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}