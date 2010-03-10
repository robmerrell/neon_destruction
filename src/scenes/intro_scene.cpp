#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  // add the logo image
  // add the logo mask
  logo = new Sprite("", 64, 64);
  logo->setX(100);
  logo->setY(100);
  addObject(logo);
  
  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  float old_x = logo->getX();
  logo->setX(old_x + 1);
  
  float old_alpha = logo->getAlpha();
  logo->setAlpha(old_alpha - 0.01);
}

