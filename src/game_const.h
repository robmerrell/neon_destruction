#include <string>

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
const int GEAR_TAG = 10;
const int IMAGE_TAG = 11;
const int TEXTURE_STRING_TAG = 12;
const int LEVEL_STRING_TAG = 13;
const int SCORE_STRING_TAG = 14;
const int MENU_TAG = 15;

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
const int TEXTURE_COUNT = 25;
const int STARS_PER_FIELD = 170;
const float STAR_FIELD1_SPEED = 100.0f;
const float STAR_FIELD2_SPEED = 50.0f;
const int PARTICLE_TOTAL = 120;

const int ANIMATE_NONE = 0;
const int ANIMATE_FADE_IN = 1;
const int ANIMATE_FADE_OUT = 2;
const float ANIMATE_FADE_SPEED = 0.75f;

/*******************
** Platform Atlas **
********************/
const float PLATFORM_SIZES[] = {24.0f, 40.0f, 72.0f, 104.0f, 126.0f, 168.0f, 201.0f, 232.0f, 276.0f, 360.0f, 401.0f};
const float PLATFORM_TEX_SIZES[] = {48.0f, 69.0f, 96.0f, 128.0f, 150.0f, 192.0f, 225.0f, 256.0f, 300.0f, 384.0f, 425.0f};
const float PLATFORM_ATLAS_Y[] = {5.0f, 40.0f, 75.0f, 110.0f, 145.0f, 180.0f, 215.0f, 250.0f, 285.0f, 320.0f, 355.0f};
const float PLATFORM_TEX_SIZE = 512.0f;

const float PLATFORM_TOP[] = {
  PLATFORM_ATLAS_Y[0] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[1] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[2] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[3] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[4] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[5] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[6] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[7] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[8] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[9] / PLATFORM_TEX_SIZE,
  PLATFORM_ATLAS_Y[10] / PLATFORM_TEX_SIZE
};

const float PLATFORM_BOTTOM[] = {
  (PLATFORM_ATLAS_Y[0] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[1] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[2] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[3] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[4] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[5] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[6] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[7] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[8] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[9] + 25.0f) / PLATFORM_TEX_SIZE,
  (PLATFORM_ATLAS_Y[10] + 25.0f) / PLATFORM_TEX_SIZE
};

const float PLATFORM_RIGHT[] = {
  PLATFORM_TEX_SIZES[0] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[1] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[2] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[3] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[4] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[5] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[6] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[7] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[8] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[9] / PLATFORM_TEX_SIZE,
  PLATFORM_TEX_SIZES[10] / PLATFORM_TEX_SIZE
};


/*****************
** Circle Atlas **
******************/
const float CIRCLE_SIZES[] = {50.0f, 40.0f, 30.0f, 20.0f};
const float CIRCLE_TEX_SIZE = 256.0F;

const float CIRCLE_TOP[] = {
  7.0f / CIRCLE_TEX_SIZE,
  16.0f / CIRCLE_TEX_SIZE,
  145.0f / CIRCLE_TEX_SIZE,
  155.0f / CIRCLE_TEX_SIZE
};

const float CIRCLE_BOTTOM[] = {
  130.0f / CIRCLE_TEX_SIZE,
  125.0f / CIRCLE_TEX_SIZE,
  230.0f / CIRCLE_TEX_SIZE,
  218.0f / CIRCLE_TEX_SIZE
};

const float CIRCLE_LEFT[] = {
  3.0f / CIRCLE_TEX_SIZE,
  133.0f / CIRCLE_TEX_SIZE,
  2.0f / CIRCLE_TEX_SIZE,
  94.0f / CIRCLE_TEX_SIZE
};

const float CIRCLE_RIGHT[] = {
  127.0f / CIRCLE_TEX_SIZE,
  242.0f / CIRCLE_TEX_SIZE,
  87.0f / CIRCLE_TEX_SIZE,
  158.0f / CIRCLE_TEX_SIZE
};


/***************
** Levels ******
****************/
const int LEVEL_COUNT = 8;
const std::string GAME_LEVELS[] = {
  "intro.xml",
  "green_vs_blue.xml",
  "gauntlet_treasure.xml",
  "clock_tower.xml",
  "steps.xml",
  "stack.xml",
  "elevator.xml",
  "bottoms_up.xml"
};
const std::string LEVEL_NAMES[] = {
  "1. Introduction",
  "2. Green vs Blue",
  "3. Gauntlet Treasure",
  "4. Clock Tower",
  "5. Steps",
  "6. Stack",
  "7. Elevator"
  "8. Bottoms up"
};


#include <Math.h>
#define RAD2DEG(Rad) ((180.0 * Rad) / M_PI)
#define DEG2RAD(Deg) ((Deg)*((M_PI)/(180.0)))

#endif