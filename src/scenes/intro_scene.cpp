#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  // add the logo image
  // add the logo mask
  Sprite *logo = new Sprite("");
  logo->setX(100);
  logo->setY(100);
  addObject(logo);
  
  // start the game loop
  scheduleLoop(1.0f/60.f);
}


void IntroScene::gameLoop() {
  
}

