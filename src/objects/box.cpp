#include "box.h"

Box::Box(float _x, float _y, float _width, float _height) : Sprite("", 64, 64, BOX_TAG) {
  x = _x;
  y = _y;
  
  width = _width;
  height = _height;
}

void Box::definePhysics(cpSpace *space) {
  // body
  cpVect verts[] = { cpv(0.0, 0.0), cpv(width, 0.0), cpv(width, -height), cpv(0.0, -height) };
  body = cpBodyNew(20.0f, cpMomentForPoly(20.0f, 4, verts, cpvzero));
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);
  
  // poly shape box
  cpShape *boxShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  boxShape->e = 0.1;
  boxShape->u = 0.3;
  boxShape->data = this;
  boxShape->collision_type = BOX_COLLISION;
  
  cpSpaceAddShape(space, boxShape);
}

void Box::display() {
  // std::cout << y << std::endl;
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  
  TexManager::Instance()->bindTexture(6);
  
  glLoadIdentity();
  glTranslatef(start_x, start_y, 0.0);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  
  // rotate if needed
  // if (dy != 0) {
  //   float angle = getInvertedMouseAngle(cpv(start_x, start_y), cpv(end_x, end_y));
  //   glRotatef(angle, 0.0, 0.0, 1.0);
  // }
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}