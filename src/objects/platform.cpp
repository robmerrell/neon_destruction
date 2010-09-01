#include "platform.h"
#include <iostream>

Platform::Platform(string sim_type) : Sprite("", 64, 64, PLATFORM_TAG) {  
  simulation_type = sim_type;
  fixed = false;
  id = "";
  
  height = 25.0f; // always 25 so that it matches our sprite
  physics_height = 12.0f;
  width = 0.0f;
  mass = 10.0f;
  friction = 0.3f;

  dir = 0;
  min_pos = 0.0f;
  max_pos = 0.0f;
  
  infinite_moment = false;
  normal_color = false;
}

void Platform::destroy(cpSpace *space) {
  if (simulation_type == "DYNAMIC")
    cpSpaceRemoveShape(space, platformShape);
  else
    cpSpaceRemoveStaticShape(space, platformShape);
    
  if (fixed) {
    cpSpaceRemoveConstraint(space, constraint);
    cpConstraintFree(constraint);
  }
    
  if (simulation_type == "DYNAMIC") cpSpaceRemoveBody(space, body);
  cpShapeFree(platformShape);
  cpBodyFree(body);
  
  if (fixed) cpBodyFree(pbody);
}

void Platform::move(int ticks) {
  float new_y = 0.0f;
  float new_x = 0.0f;
  
  if (dir == 0) {
    new_y = pbody->p.y + (PLATFORM_SPEED * (ticks * 0.001));
    new_x = x;
    if (new_y >= max_pos) dir = 1;
  } else if (dir == 1) {
    new_y = pbody->p.y - (PLATFORM_SPEED * (ticks * 0.001));
    new_x = x;
    if (new_y <= min_pos) dir = 0;
  } else if (dir == 2) {
    new_x = pbody->p.x + (PLATFORM_SPEED * (ticks * 0.001));
    new_y = y;
    if (new_x >= max_pos) dir = 3;
  } else if (dir == 3) {
    new_x = pbody->p.x - (PLATFORM_SPEED * (ticks * 0.001));
    new_y = y;
    if (new_x <= min_pos) dir = 2;
  }
  
  pbody->p = cpv(new_x, new_y);
}

void Platform::setMoveable(float _min, float _max, int _dir) {
  max_pos = _max;
  min_pos = _min;
  dir = _dir;
  moves = true;
}

bool Platform::moveable() {
  return moves;
}

void Platform::setWidth(float _width) {
  width = _width;
}

void Platform::setMass(float _m) {
  mass = _m;
}

void Platform::setFriction(float _f) {
  friction = _f;
}

cpBody* Platform::getBody() {
  return body;
}

void Platform::definePhysics(cpSpace *space) {
  // body
  cpVect verts[] = { cpv(-width/2 + 9, -3), cpv(-width/2 + 9, 3), cpv(width/2 - 9, 3), cpv(width/2 - 9, -3) };
  if (simulation_type == "DYNAMIC") {
    if (!infinite_moment)
      body = cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero));
    else
      body = cpBodyNew(mass, INFINITY);
  } else
    body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);
  
  // poly shape box
  platformShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  platformShape->e = 0.1;
  platformShape->u = friction;
  platformShape->data = this;
  platformShape->collision_type = PLATFORM_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, platformShape);
  else
    cpSpaceAddStaticShape(space, platformShape);
}

void Platform::applyImpulse(float impx, float impy) {
  cpBodyApplyImpulse(body, cpv(impx, impy), cpv(x - impx, y - impy));
}

void Platform::fix(cpSpace *space) {
  pbody = cpBodyNew(INFINITY, INFINITY);
  pbody->p = cpv(x, y);

  constraint = cpSpaceAddConstraint(space, cpPivotJointNew(body, pbody, cpv(x,y)));
  fixed = true;
}

void Platform::infiniteMoment() {
  infinite_moment = true;
}

void Platform::infiniteNormalColor() {
  normal_color = true;
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
  
  if (simulation_type == "STATIC" || (infinite_moment && !normal_color))
    TexManager::Instance()->bindTexture(7);
  else
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