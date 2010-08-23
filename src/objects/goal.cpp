#include "goal.h"

Goal::Goal(float x, float y) : Sprite("", 64, 64, GOAL_TAG) {
  setX(x);
  setY(y);
}

void Goal::destroy(cpSpace *space) {
  cpSpaceRemoveShape(space, goalShape);
  cpSpaceRemoveBody(space, body);
  cpShapeFree(goalShape);
  cpBodyFree(body);
}

void Goal::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(20.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // goal shape
  goalShape = cpCircleShapeNew(body, 19.0f, cpvzero);
  goalShape->e = 0.5;
  goalShape->u = 0.3;
  goalShape->data = this;
  goalShape->collision_type = GOAL_COLLISION;
  cpSpaceAddShape(space, goalShape);
}

cpBody* Goal::getBody() {
  return body;
}

void Goal::display() {
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
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  TexManager::Instance()->bindTexture(9);
  
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