#include "gear.h"
#include <iostream>

Gear::Gear() : Sprite("", 64, 64, GEAR_TAG) {  
  height = 25.0f; // always 25 so that it matches our sprite
  physics_height = 12.0f;
  width = 0.0f;
}

void Gear::destroy(cpSpace *space) {
  cpSpaceRemoveShape(space, platformShape);
  cpSpaceRemoveShape(space, platformShape2);
  cpSpaceRemoveBody(space, body);
  cpShapeFree(platformShape);
  cpShapeFree(platformShape2);
  cpBodyFree(body);
}

void Gear::setWidth(float _width) {
  width = _width;
}

void Gear::definePhysics(cpSpace *space) {  
  // body
  cpVect verts[] = { cpv(-width/2, -physics_height/2), cpv(-width/2, physics_height/2), cpv(width/2, physics_height/2), cpv(width/2, -physics_height/2) };
  cpVect pverts[] = { cpv(-physics_height/2, -width/2), cpv(-physics_height/2, width/2), cpv(physics_height/2, width/2), cpv(physics_height/2, -width/2) } ;
  body = cpBodyNew(10.0f, cpMomentForPoly(10.0f, 4, verts, cpvzero));
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  cpSpaceAddBody(space, body);
  
  // poly shape box
  platformShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  platformShape->e = 0.1;
  platformShape->u = 0.3;
  platformShape->data = this;
  cpSpaceAddShape(space, platformShape);
    
  platformShape2 = cpPolyShapeNew(body, 4, pverts, cpvzero);
  platformShape2->e = 0.1;
  platformShape2->u = 0.3;
  platformShape2->data = this;
  cpSpaceAddShape(space, platformShape2);

  pbody = cpBodyNew(INFINITY, INFINITY);
  pbody->p = cpv(x, y);
  cpSpaceAddConstraint(space, cpPivotJointNew(body, pbody, cpv(x,y)));
}

void Gear::display() {
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
  
  TexManager::Instance()->bindTexture(14);
  
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
  
  glTranslatef(width/2.0f + height/2.0f, width/2.0f - height/2.0f, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}