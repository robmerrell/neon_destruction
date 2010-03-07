#include "sprite.h"

Sprite::Sprite(std::string filename, float _width, float _height) {
  width = _width;
  height = _height;
}

void Sprite::display() {
  glTranslatef(0.0, 0.0, 0.0);
  
  glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertex2i(0, height);
    glVertex2i(0, 0);
    glVertex2i(width, height);
    
    glVertex2i(width, 0);
    glVertex2i((width / 2), height);
    glVertex2i((width / 2), 0);
  glEnd();
}

float Sprite::getX() {
  return x;
}

void Sprite::setX(float _x) {
  x = _x;
  glTranslatef(x, 0.0, 0.0);
}

float Sprite::getY() {
  return y;
}

void Sprite::setY(float _y) {
  y = _y;
  glTranslatef(0.0, y, 0.0);
}

float Sprite::getWidth() {
  return width;
}

float Sprite::getHeight() {
  return height;
}