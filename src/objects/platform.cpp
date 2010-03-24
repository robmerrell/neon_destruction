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
  cpShape *platformShape = cpSegmentShapeNew(body, cpv(start_x, start_y), cpv(end_x, end_y), 2.0f);
  platformShape->e = 0.5;
  platformShape->u = 0.3;
  platformShape->collision_type = PLATFORM_COLLISION;
  
  cpSpaceAddStaticShape(space, platformShape);
}