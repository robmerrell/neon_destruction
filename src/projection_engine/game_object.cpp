#include "game_object.h"

float GameObject::getX() {
  return x;
}

void GameObject::setX(float _x) {
  if (_x != x)
    glTranslatef(_x - x, 0.0, 0.0);
  
  x = _x;
}

float GameObject::getY() {
  return y;
}

void GameObject::setY(float _y) {
  if (_y != y)
    glTranslatef(0.0, _y - y, 0.0);
  
  y = _y;
}

float GameObject::getAlpha() {
  return alpha;
}

void GameObject::setAlpha(float _alpha) {
  alpha = _alpha;
}