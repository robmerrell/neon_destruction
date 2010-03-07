#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  // add the logo image
  // add the logo mask
  Sprite *logo = new Sprite("");
  addObject(logo);
  
  // start the game loop
  scheduleLoop(1.0f/60.f);
}


void IntroScene::gameLoop() {
  
  
  //   glBegin(GL_TRIANGLE_STRIP);
  //     glColor4f(1.0,1.0,1.0,1.0);
  //  glTexCoord2f(0.1, 0.9); glVertex2i(0,200); //v0
  //  glTexCoord2f(0.1, 0.1); glVertex2i(0, 0);    //v1
  //  glTexCoord2f(0.9, 0.9); glVertex2i(200,200);     ///v2
  //  glTexCoord2f(0.9, 0.1); glVertex2i(200,0);  //v3
  //  glTexCoord2f(0.9, 0.9); glVertex2i(400,200);   //v4
  //  glTexCoord2f(0.9, 0.1); glVertex2i(400, 0);    //v5
  // glEnd();
}

