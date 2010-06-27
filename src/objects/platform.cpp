#include "platform.h"
#include <iostream>

Platform::Platform() : Sprite("", 64, 64, PLATFORM_TAG) {  
  height = 32.0f; // always 32 so that it matches our sprite
  physics_height = 12.0f;
  width = 0.0f;
}

void Platform::destroy(cpSpace *space) {
  cpSpaceRemoveStaticShape(space, platformShape);
  cpSpaceRemoveBody(space, body);
  cpShapeFree(platformShape);
  cpBodyFree(body);
}

void Platform::setWidth(float _width) {
  width = _width;
}

void Platform::definePhysics(cpSpace *space) {  
  // body
  cpVect verts[] = { cpv(-width/2, -physics_height/2), cpv(-width/2, physics_height/2), cpv(width/2, physics_height/2), cpv(width/2, -physics_height/2) };
  body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  
  // poly shape box
  platformShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  platformShape->e = 0.1;
  platformShape->u = 0.3;
  platformShape->data = this;
  platformShape->collision_type = PLATFORM_COLLISION;
  
  cpSpaceAddStaticShape(space, platformShape);
}

void Platform::display() {
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  TexManager::Instance()->bindTexture(6);
  
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