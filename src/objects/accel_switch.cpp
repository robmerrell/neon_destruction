#include "accel_switch.h"

AccelSwitch::AccelSwitch(float _x, float _y) : Sprite("", 64, 64, ACCEL_SWITCH_TAG) {
  setX(_x);
  setY(_y);
  should_block = false;
}

void AccelSwitch::destroy(cpSpace *space) {
  cpSpaceRemoveStaticShape(space, switchShape);
  cpShapeFree(switchShape);
  cpBodyFree(body);
}

void AccelSwitch::definePhysics(cpSpace *space) {
  float width = 36.0f;
  float height = 36.0f;
  
  cpVect verts[] = { cpv(-width/2, -height/2), cpv(-width/2, height/2), cpv(width/2, height/2), cpv(width/2, -height/2) };
  body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  
  // poly shape
  switchShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  switchShape->sensor = 1;
  switchShape->e = 0.1;
  switchShape->u = 0.3;
  switchShape->data = this;
  switchShape->collision_type = ACCEL_SWITCH_COLLISION;
  
  cpSpaceAddStaticShape(space, switchShape);
}

void AccelSwitch::block() {
  should_block = true;
}

void AccelSwitch::display() {
  float start_x = x;
  float start_y = y;
  
  float width = 48.0f;
  float height = 48.0f;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  if (!should_block)
    glColor4f(alpha, alpha, alpha, alpha);
  else
    glColor4f(0.3f, 0.3f, 0.3f, alpha);
  
  TexManager::Instance()->bindTexture(18);
  
  glLoadIdentity();
  glTranslatef(start_x - width/2, start_y + height/2, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}