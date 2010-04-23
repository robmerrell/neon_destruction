#include <Math.h>
#include "GLES/gl.h"
#include "../chipmunk/headers/chipmunk.h"

#include "../game_const.h"

#ifndef EVENT_TRANSLATIONS_H
#define EVENT_TRANSLATIONS_H

/**
 * Get the translated coordinates for a mouse event
 */
cpVect translatedMouseCoords(float, float);

/**
 * Get the inverted angle in degrees for the mouse event
 * cpVect origin coords
 * cpVect mouse coords
 */
float getInvertedMouseAngle(cpVect, cpVect);
 
 
/**
 * Get the angle in radians for the mouse event
 * cpVect origin coords
 * cpvect mouse coords
 */
float getMouseRadians(cpVect, cpVect);

#endif
