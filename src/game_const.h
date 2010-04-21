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

const int CANNON_COLLISION = 1;
const int BALL_COLLISION = 2;
const int PLATFORM_COLLISION = 3;
const int GOAL_COLLISION = 4;
const int GRAVITY_SWITCH_COLLISION = 5;

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
** Textures **
**************/
const int TEXTURE_COUNT = 2;

#endif