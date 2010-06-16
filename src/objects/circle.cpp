#include "circle.h"
#include <Math.h>

Circle::Circle(string sim_type) : Sprite("", 64, 64, CIRCLE_TAG) {
}

void Circle::setRadius(float _rad) {
  radius = _rad;
}

void Circle::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(10.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // ball shape
  cpShape *ballShape = cpCircleShapeNew(body, radius, cpvzero);
  ballShape->e = 0.8;
  ballShape->u = 0.2;
  ballShape->data = this;
  ballShape->collision_type = CIRCLE_COLLISION;
  cpSpaceAddShape(space, ballShape);
}

void Circle::display() {
  float diameter = radius * radius;
  
  GLfloat circle_vertices[] = {0,diameter,0, diameter,diameter,0, 0,0,0, diameter,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  TexManager::Instance()->bindTexture(10);
  
  glLoadIdentity();
  glTranslatef(body->p.x, body->p.y, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, circle_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}