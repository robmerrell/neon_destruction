#include "cannon.h"

Cannon::Cannon(float x, float y) : Sprite("", 64, 64, CANNON_TAG) {
  setX(x);
  setY(y);
  turret_angle = 0;
  orientation = "S";
}

void Cannon::setOrientation(string _o) {
  orientation = _o;
  
  if (_o == string("S"))
    angle = 0.0f;
  else if (_o == string("N")) 
    angle = 180.0f;
  else if (_o == string("W"))
    angle = 90.0f;
  else if (_o == string("E")) {
    angle = 270.0f;
    turret_angle = 180.0f;
  }
}

void Cannon::display() {
  GLfloat base_vertices[] = {0,128,0, 128,128,0, 0,0,0, 128,0,0};
  GLfloat base_tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  glColor4f(alpha, alpha, alpha, alpha);

  TexManager::Instance()->bindTexture(3);
  
  float bx = x;
  float by = y;
  
  if (angle == 180.0f) by -= 26.0f;
  else if (angle == 90.0f) {
    bx -= 12.0f;
    by -= 12.0f;
  } else if (angle == 270.0f) {
    bx += 12.0f;
    by -= 12.0f;
  }
  
  // place and rotate the base
  glLoadIdentity();
  glTranslatef(bx, by, 0);
  glTranslatef(64.0f, 64.0f, 0.0f);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-64.0f, -64.0f, 0.0f);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, base_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, base_tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  

  
  GLfloat turret_vertices[] = {0,128,0, 128,128,0, 0,0,0, 128,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  TexManager::Instance()->bindTexture(2);
  
  // place and rotate the turret
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glTranslatef(64.0f, 51.0f, 0.0);
  glRotatef(turret_angle, 0.0, 0.0, 1.0);
  glTranslatef(-64.0f, -51.0f, 0.0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, turret_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cannon::rotateTurret(float angle) {
  turret_angle = angle;
}

cpVect Cannon::translatedCoords() {
  return cpv(getX() + 31, getY()); 
}
