#include "platform.h"

Platform::Platform(float sx, float sy, float ex, float ey) : Sprite("", 64, 64, PLATFORM_TAG) {
  start_x = sx;
  start_y = sy;
  
  end_x = ex;
  end_y = ey;
}

void Platform::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(INFINITY, INFINITY);

  // segment
  cpShape *platformShape = cpSegmentShapeNew(body, cpv(start_x, start_y), cpv(end_x, end_y), 3.0f);
  platformShape->e = 0.5;
  platformShape->u = 0.3;
  platformShape->collision_type = PLATFORM_COLLISION;
  
  cpSpaceAddStaticShape(space, platformShape);
}

void Platform::display() {
  glLineWidth(4.0);
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_LINE_SMOOTH);
  
  // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  
  /*
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,6,0, dx,6,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  
  TexManager::Instance()->bindTexture(6);
  
  glLoadIdentity();
  glTranslatef(start_x, start_y, 0.0);
  
  // rotate if needed
  if (dy != 0) {
    float angle = getInvertedMouseAngle(cpv(start_x, start_y), cpv(end_x, end_y));
    glRotatef(angle, 0.0, 0.0, 1.0);
  }
  
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  */
  glLoadIdentity();
  glTranslatef(0, 0, 0);
  
  GLfloat vertices[] = {start_x, start_y, end_x, end_y};
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawArrays(GL_LINES, 0, 2);
  glDisableClientState(GL_VERTEX_ARRAY);
  
  glEnable(GL_TEXTURE_2D);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
  
  
  
  /*
  // draw the glow
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat glow_vertices[] = {0,32,0, dx,32,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  TexManager::Instance()->bindTexture(7);
  
  glLoadIdentity();
  glTranslatef(start_x, start_y, 0.0);
  
  // rotate if needed
  // if (dy != 0) {
  //   float angle = getInvertedMouseAngle(cpv(start_x, start_y), cpv(end_x, end_y));
  //   glRotatef(angle, 0.0, 0.0, 1.0);
  // }
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, glow_vertices);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  */
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  float distance = sqrt((dx*dx) - (dy * dy));
  
  GLfloat shadow_vertices[] = {0,32,0, distance,32,0, 0,0,0, distance,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  TexManager::Instance()->bindTexture(7);
  
  glLoadIdentity();
  glTranslatef(start_x, start_y - 16, 0.0);
  
  // rotate if needed
  if (dy != 0) {
    float angle = getInvertedMouseAngle(cpv(start_x, start_y), cpv(end_x, end_y));
    glRotatef(angle, 0.0, 0.0, 1.0);
  }
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, shadow_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
  
  
  
  /*
  // GLfloat ball_vertices[] = {0,6,0, ,6,0, 0,0,0, 64,0,0};
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,6,0, dx,6,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  
  TexManager::Instance()->bindTexture(6);
  
  glLoadIdentity();
  glTranslatef(start_x, start_y, 0.0);
  
  // rotate if needed
  if (dy != 0) {
    float angle = getInvertedMouseAngle(cpv(start_x, start_y), cpv(end_x, end_y));
    glRotatef(angle, 0.0, 0.0, 1.0);
  }
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
  */
}