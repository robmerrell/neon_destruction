#include "SDL_opengl.h"
#include "chipmunk/chipmunk.h"

#include <math.h>
#include <stdio.h>

#ifndef DRAW_PHYSICS_H
#define DRAW_PHYSICS_H

#define BODY_COLOR 1.0f, 0.0f, 0.0f, 1.0f

void drawPhysics(cpSpace*);

#endif