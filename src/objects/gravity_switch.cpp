#include "gravity_switch.h"

GravitySwitch::GravitySwitch(float _x, float _y, int _direction) : Sprite("", 64, 64, GRAVITY_SWITCH_TAG) {
  direction = _direction;
  
  setX(_x);
  setY(_y);
}

void GravitySwitch::destroy(cpSpace *space) {
  cpSpaceRemoveStaticShape(space, switchShape);
  cpSpaceRemoveBody(space, body);
  cpShapeFree(switchShape);
  cpBodyFree(body);
}

void GravitySwitch::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);

  // goal shape
  switchShape = cpCircleShapeNew(body, 15.0, cpvzero);
  switchShape->e = 0.5;
  switchShape->u = 0.3;
  switchShape->data = this;
  switchShape->collision_type = GRAVITY_SWITCH_COLLISION;
  cpSpaceAddStaticShape(space, switchShape);
}

int GravitySwitch::getDirection() {
  return direction;
}

void GravitySwitch::display() {
  float start_x = x;
  float start_y = y;
  
  float width = 32.0f;
  float height = 32.0f;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  TexManager::Instance()->bindTexture(8);
  
  glLoadIdentity();
  glTranslatef(start_x - width/2, start_y + height/2, 0.0);
  glTranslatef(width/2, -height/2, 0.0);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-width/2, height/2, 0.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}