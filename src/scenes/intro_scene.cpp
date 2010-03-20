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

}

