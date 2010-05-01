#include "sprite.h"

Sprite::Sprite(std::string filename, float _width, float _height, int _tag) {
  width = _width;
  height = _height;
  tag = _tag;
  angle = 0.0;
  
  alpha = 1;
}

void Sprite::setAngle(float _angle) {
  angle = _angle;
}

float Sprite::getAngle() {
  return angle;
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