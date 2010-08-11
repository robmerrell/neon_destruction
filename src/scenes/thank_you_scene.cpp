#include "thank_you_scene.h"

ThankYouScene::ThankYouScene() {
  quit = false;
}

ThankYouScene::~ThankYouScene() {}

bool ThankYouScene::setup() {
  TextureString *string = new TextureString(10.0f, 30.0f, "Thank you for beta testing!");
  addObject(string);
  
  TextureString *feed = new TextureString(100.0f, 100.0f, "Please send feedback to:");
  addObject(feed);
  
  TextureString *email = new TextureString(100.0f, 130.0f, "robmerrell@trackera.com");
  addObject(email);
  
  TextureString *twitter = new TextureString(100.0f, 160.0f, "or @robmerrell on Twitter");
  addObject(twitter);
  
  TextureString *exit = new TextureString(125.0f, 300.0f, "Tap to quit");
  addObject(exit);
  
  gameLoop();
  
  delete string;
  delete feed;
  delete email;
  delete twitter;
  
  return quit;
}


void ThankYouScene::gameLoop() {
  in_loop = true;
    
  float accumulator = 0.0f;
  int millistep = 16;
  float timeStep = float(millistep)/1000;
  fps.start();
  animation.start();
  animation_ticks = 0;
    
  while (in_loop) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        in_loop = false;
        quit = true;
      } else if (event.type == SDL_MOUSEBUTTONUP) {
        in_loop = false;
        quit = true;
      }
    }
    
    animation_ticks = fps.get_ticks();
    
    if (animation_ticks > 32) animation_ticks = 32;
    
    accumulator += animation_ticks;
    fps.start();
    
    while (accumulator >= millistep) {
      accumulator -= millistep;
    }
    
    glDisable(GL_BLEND);
    
    // draw the background
    // moveBackground(animation_ticks);
    updateAnimation(animation_ticks);
    // drawBackground();
    
    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

    // display
    vector<Sprite*>::iterator sprite;
    for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
      (*sprite)->display();
    }
    
    // update the screen
    SDL_GL_SwapBuffers();
    
    if (animation.get_ticks() >= 3000) {
      for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
        (*sprite)->setAnimationState(ANIMATE_FADE_OUT);
      }
    }
  }
}