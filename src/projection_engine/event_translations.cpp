#include "event_translations.h"

cpVect translatedMouseCoords(float x, float y) {
  float mouse_x, mouse_y;
  
  #ifdef DEVICE
    mouse_x = y;
    mouse_y = SCREEN_HEIGHT - x;
  #else
    mouse_x = x;
    mouse_y = y;
  #endif
  
  return cpv(mouse_x, mouse_y);
}

float getInvertedMouseAngle(cpVect origin, cpVect mouse) {
  float delta_x = mouse.x - origin.x;
  float delta_y = mouse.y - origin.y;
  float angle = 180 + (atan2(-delta_y, -delta_x) * (180/M_PI));  
  
  return angle;
}

float getMouseRadians(cpVect origin, cpVect mouse) {
  float delta_x = mouse.x - origin.x;
  float delta_y = mouse.y - origin.y;
  float angle = 180 + (atan2(delta_y, -delta_x) * (180/M_PI));
  float radians = angle * (M_PI/180);
  
  return radians;
}