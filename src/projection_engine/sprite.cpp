#include "sprite.h"

Sprite::Sprite(std::string filename) {
}

void Sprite::display() {
  glTranslatef(0.0, 0.0, 0.0);
  
  glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertex2i(0, 100);
    glVertex2i(0, 0);
    glVertex2i(100, 100);
    
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex2i(100, 0);
    glVertex2i(200, 100);
    glVertex2i(200, 0);
  glEnd();
}

float Sprite::getX() {
  return x;
}

void Sprite::setX(float new_x) {
  x = new_x;
  glTranslatef(x, 0.0, 0.0);
}

float Sprite::getY() {
  return y;
}

void Sprite::setY(float new_y) {
  y = new_y;
  glTranslatef(0.0, y, 0.0);
}

float Sprite::getWidth() {
  return width;
}

float Sprite::getHeight() {
  return height;
}