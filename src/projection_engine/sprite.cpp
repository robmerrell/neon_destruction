#include "sprite.h"

Sprite::Sprite(std::string filename, float _width, float _height) {
  width = _width;
  height = _height;
  
  alpha = 1;
}

void Sprite::display() {
  glLoadIdentity();
  glTranslatef(x, y, 0.0);
  
  glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0, 0.0, 0.0, alpha);
    glVertex2i(0, height);
    glVertex2i(0, 0);
    glVertex2i(width, height);
    
    glColor4f(0.0, 1.0, 0.0, alpha);
    glVertex2i(width, 0);
    glVertex2i(width, height);
    glVertex2i(width, 0);
  glEnd();
}

float Sprite::getWidth() {
  return width;
}

float Sprite::getHeight() {
  return height;
}