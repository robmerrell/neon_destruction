#include "SDL.h"
#include "GLES/gl.h"

#include "../game_const.h"
#include "../chipmunk/headers/chipmunk.h"

#include <Math.h>
#include <iostream>

#ifndef DRAW_PHYSICS_H
#define DRAW_PHYSICS_H

#define DEGREES_TO_RADIANS(x) (3.14159265358979323846 * x / 180.0)

void draw_chipmunk(cpSpace*);

static void draw_shapes(void*, void*);

static void draw_circle(cpBody*, cpCircleShape*);

static void draw_segment(cpBody*, cpSegmentShape*);

static void draw_poly(cpBody*, cpPolyShape*);

static void draw_constraint(cpConstraint*);

#endif