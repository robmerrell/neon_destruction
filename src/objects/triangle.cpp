#include "triangle.h"

Triangle::Triangle(string sim_type) : Sprite("", 64, 64, BOX_TAG) {
  simulation_type = sim_type;

  x = 0.0f;
  y = 0.0f;
  width = 0.0f;
  height = 0.0f;  
}

void Triangle::setWidth(float _width) {
  width = _width;
}

void Triangle::setHeight(float _height) {
  height = _height;
}

void Triangle::definePhysics(cpSpace *space) {
  // body
  // cpVect verts[] = { cpv(-width/2, -height/2), cpv(-width/2, height/2), cpv(width/2, height/2), cpv(width/2, -height/2) };
  // cpVect verts[] = { cpv((-width/2)/2, (-height/2)/2), cpv(-width/2, height/2), cpv(width/2, height/2) };
  // cpVect verts[] = { cpv(-width/2, -height/2), cpv((width/2)/2, (height/2)/2),cpv(width/2, -height/2) };
  cpVect verts[] = { cpv(-width/2, -height/2), cpv((width/2)/4, (height/2)),cpv(width/2, -height/2) };
  if (simulation_type == "DYNAMIC")
    body = cpBodyNew(10.0f, cpMomentForPoly(10.0f, 3, verts, cpvzero));
  else
    body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);
  
  // poly shape triangle
  cpShape *triangleShape = cpPolyShapeNew(body, 3, verts, cpvzero);
  triangleShape->e = 0.1;
  triangleShape->u = 0.3;
  triangleShape->data = this;
  triangleShape->collision_type = TRIANGLE_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, triangleShape);
  else
    cpSpaceAddStaticShape(space, triangleShape);
}

void Triangle::display() {
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  
  TexManager::Instance()->bindTexture(11);
  
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