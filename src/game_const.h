#ifndef GAME_CONST_H
#define GAME_CONST_H

/************
** Physics **
*************/
const int GRAVITY_RATE = 400;

const int CANNON_TAG = 1;
const int BALL_TAG = 2;
const int PLATFORM_TAG = 3;
const int GOAL_TAG = 4;
const int GRAVITY_SWITCH_TAG = 5;
const int BOX_TAG = 6;
const int CROSSHAIR_TAG = 7;
const int CIRCLE_TAG = 8;
const int TRIANGLE_TAG = 9;

const int CANNON_COLLISION = 1;
const int BALL_COLLISION = 2;
const int PLATFORM_COLLISION = 3;
const int GOAL_COLLISION = 4;
const int GRAVITY_SWITCH_COLLISION = 5;
const int BOX_COLLISION = 6;
const int CIRCLE_COLLISION = 7;
const int TRIANGLE_COLLISION = 8;

const int GRAVITY_UP = 1;
const int GRAVITY_DOWN = 2;
const int GRAVITY_LEFT = 3;
const int GRAVITY_RIGHT = 4;


/************
** WINDOW **
************/
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;


/*************
** Graphics **
**************/
const int TEXTURE_COUNT = 12;
const int STARS_PER_FIELD = 170;
const float STAR_FIELD1_SPEED = 100.0f;
const float STAR_FIELD2_SPEED = 50.0f;


#include <Math.h>
#define RAD2DEG(Rad) ((180.0 * Rad) / M_PI)
#define DEG2RAD(Deg) ((Deg)*((M_PI)/(180.0)))

#endif