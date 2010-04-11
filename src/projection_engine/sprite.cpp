#include "sprite.h"

Sprite::Sprite(std::string filename, float _width, float _height, int _tag) {
  width = _width;
  height = _height;
  tag = _tag;
  
  alpha = 1;
}

void Sprite::display() {
  glLoadIdentity();
  glTranslatef(x, y, 0.0);
}

float Sprite::getWidth() {
  return width;
}

float Sprite::getHeight() {
  return height;
}

int Sprite::getTag() {
  return tag;
}