#include "circle.h"
#include <Math.h>

Circle::Circle(string sim_type) : Sprite("", 64, 64, CIRCLE_TAG) {
  simulation_type = sim_type;
  elasticity = 0.8f;
  egg = false;
}

void Circle::destroy(cpSpace *space) {
  if (simulation_type == "DYNAMIC")
    cpSpaceRemoveShape(space, circleShape);
  else
    cpSpaceRemoveStaticShape(space, circleShape);
    
  if (simulation_type == "DYNAMIC") cpSpaceRemoveBody(space, body);
  cpShapeFree(circleShape);
  cpBodyFree(body);
}

void Circle::setRadius(float _rad) {
  radius = _rad;
  mass = radius/7.0f;
}

void Circle::setElasticity(float _el) {
  elasticity = _el;
}

void Circle::setMass(float _m) {
  mass = _m;
}

cpBody* Circle::getBody() {
  return body;
}

void Circle::eColl() {
  egg = true;
}

void Circle::definePhysics(cpSpace *space) {
  // body
  if (simulation_type == "DYNAMIC")
    body = cpBodyNew(mass, cpMomentForCircle(mass, 0.0f, radius, cpvzero));
  else
    body = cpBodyNew(INFINITY, INFINITY);
    
  body->p = cpv(x, y);
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);

  // ball shape
  circleShape = cpCircleShapeNew(body, radius, cpvzero);
  circleShape->e = elasticity;
  circleShape->u = 0.2;
  circleShape->data = this;
  if (!egg)
    circleShape->collision_type = CIRCLE_COLLISION;
  else
    circleShape->collision_type = EGG_CIRCLE_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, circleShape);
  else
    cpSpaceAddStaticShape(space, circleShape);
}

void Circle::display() {
  float diameter = radius * 2.0f;
  
  // get the points in the texture map
  int ti = 0;
  for (int i = 0; i < 4; i++) {
    if (CIRCLE_SIZES[i] == radius)
      ti = i;
  }
  
  float dx = (CIRCLE_RIGHT[ti]*CIRCLE_TEX_SIZE) - (CIRCLE_LEFT[ti]*CIRCLE_TEX_SIZE);
  float dy = (CIRCLE_TOP[ti]*CIRCLE_TEX_SIZE) - (CIRCLE_BOTTOM[ti]*CIRCLE_TEX_SIZE);
  
  GLfloat circle_vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {CIRCLE_LEFT[ti],CIRCLE_BOTTOM[ti],0, CIRCLE_RIGHT[ti],CIRCLE_BOTTOM[ti],0, CIRCLE_LEFT[ti],CIRCLE_TOP[ti],0, CIRCLE_RIGHT[ti],CIRCLE_TOP[ti],0};
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  
  if (simulation_type == "DYNAMIC")
    TexManager::Instance()->bindTexture(16);
  else
    TexManager::Instance()->bindTexture(15);
  
  glLoadIdentity();
  glTranslatef(body->p.x - dx/2.0f, body->p.y - dy/2.0f, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, circle_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}