#include "platform.h"
#include <iostream>

Platform::Platform(string sim_type) : Sprite("", 64, 64, PLATFORM_TAG) {  
  simulation_type = sim_type;
  fixed = false;
  
  height = 25.0f; // always 25 so that it matches our sprite
  physics_height = 12.0f;
  width = 0.0f;
}

void Platform::destroy(cpSpace *space) {
  if (simulation_type == "DYNAMIC")
    cpSpaceRemoveShape(space, platformShape);
  else
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
  if (simulation_type == "DYNAMIC")
    body = cpBodyNew(10.0f, cpMomentForPoly(10.0f, 4, verts, cpvzero));
  else
    body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);
  
  // poly shape box
  platformShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  platformShape->e = 0.1;
  platformShape->u = 0.3;
  platformShape->data = this;
  platformShape->collision_type = PLATFORM_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, platformShape);
  else
    cpSpaceAddStaticShape(space, platformShape);
}

void Platform::fix(cpSpace *space) {
  pbody = cpBodyNew(INFINITY, INFINITY);
  pbody->p = cpv(x, y);

  cpSpaceAddConstraint(space, cpPivotJointNew(body, pbody, cpv(x,y)));
  fixed = true;
}

void Platform::display() {
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  int ti = 0; // texture index
  
  // get the points in the texture map
  for (int i = 0; i < sizeof(PLATFORM_SIZES)/sizeof(int); i++) {
    if (PLATFORM_SIZES[i] == width)
      ti = i;
  }
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,PLATFORM_BOTTOM[ti],0, PLATFORM_RIGHT[ti],PLATFORM_BOTTOM[ti],0, 0,PLATFORM_TOP[ti],0, PLATFORM_RIGHT[ti],PLATFORM_TOP[ti],0};
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  if (simulation_type == "DYNAMIC")
    TexManager::Instance()->bindTexture(14);
  else
    TexManager::Instance()->bindTexture(13);
  
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