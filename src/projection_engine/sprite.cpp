#include "sprite.h"

Sprite::Sprite(std::string filename, float _width, float _height, int _tag) {
  width = _width;
  height = _height;
  tag = _tag;
  angle = 0.0;
  
  alpha = 0.0f;
  animation_state = ANIMATE_FADE_IN;
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

void Sprite::setTag(int _t) {
  tag = _t;
}

int Sprite::getAnimationState() {
  return animation_state;
}

void Sprite::setAnimationState(int state) {
  animation_state = state;
}