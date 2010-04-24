#include "cannon.h"

Cannon::Cannon(float x, float y) : Sprite("", 64, 64, CANNON_TAG) {
  setX(x);
  setY(y);
  turret_angle = 0;
}

void Cannon::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);

  // segment
  cpShape *shape = cpSegmentShapeNew(body, cpv(0, 0), cpv(2, 2), 1.0f);
  shape->e = 0.5;
  shape->u = 0.3;
  shape->collision_type = CANNON_COLLISION;
  
  cpSpaceAddStaticShape(space, shape);
}

void Cannon::display() {
  GLfloat base_vertices[] = {0,64,0, 64,64,0, 0,0,0, 64,0,0};
  GLfloat base_tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  TexManager::Instance()->bindTexture(5);
  
  // place and rotate the turret
  glLoadIdentity();
  glTranslatef(body->p.x, body->p.y, 0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, base_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, base_tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  

  
  GLfloat turret_vertices[] = {0,128,0, 128,128,0, 0,0,0, 128,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  TexManager::Instance()->bindTexture(3);
  
  // place and rotate the turret
  glLoadIdentity();
  glTranslatef(body->p.x - 11, body->p.y - 61, 0);
  glTranslatef(42, 67, 0.0);
  glRotatef(turret_angle, 0.0, 0.0, 1.0);
  glTranslatef(-42, -67, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, turret_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cannon::rotateTurret(float angle) {
  turret_angle = angle;
}

cpVect Cannon::translatedCoords() {
  return cpv(getX() + 31, getY()); 
}