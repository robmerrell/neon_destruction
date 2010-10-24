#include "title_scene.h"

TitleScene::TitleScene() {
  quit = false;
  loaded = false;
  playing_music = false;
}

TitleScene::~TitleScene() {}

bool TitleScene::setup() {
  Image *image;

  image = new Image(0.0f, 0.0f, 512.0f, 512.0f, 0);
  image->setAlpha(1.0f);
  addObject(image);
  
  gameLoop();
  
  delete image;
  
  return quit;
}


void TitleScene::gameLoop() {
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
    updateAnimation(animation_ticks);
    
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
    
    if (!loaded) {
      TexManager::Instance()->loadTexture("assets/ball.png", true);
      TexManager::Instance()->loadTexture("assets/cannon_top.png", true);
      TexManager::Instance()->loadTexture("assets/cannon_base.png", true);
      TexManager::Instance()->loadTexture("assets/crosshairs.png", true);
      TexManager::Instance()->loadTexture("assets/circle.png", true);
      TexManager::Instance()->loadTexture("assets/particle.png", true);
      TexManager::Instance()->loadTexture("assets/blue_platform_atlas.png", true);
      TexManager::Instance()->loadTexture("assets/green_platform_atlas.png", true);
      TexManager::Instance()->loadTexture("assets/goal.png", true);
      TexManager::Instance()->loadTexture("assets/gravity_switch.png", true);
      TexManager::Instance()->loadTexture("assets/font.png", true);
      TexManager::Instance()->loadTexture("assets/menu.png", true);
      TexManager::Instance()->loadTexture("assets/sound_highlight.png", true);
      TexManager::Instance()->loadTexture("assets/go_to_level.png", true);
      TexManager::Instance()->loadTexture("assets/blue_circle_atlas.png", true);
      TexManager::Instance()->loadTexture("assets/green_circle_atlas.png", true);
      TexManager::Instance()->loadTexture("assets/arrow_down.png", true);
      TexManager::Instance()->loadTexture("assets/accel_switch.png", true);
      TexManager::Instance()->loadTexture("assets/star.png", true);
      TexManager::Instance()->loadTexture("assets/end_level.png", true);
      TexManager::Instance()->loadTexture("assets/font_large.png", true);
      TexManager::Instance()->loadTexture("assets/categories.png", true);
      
      SoundManager::Instance()->loadMusic("assets/music.mp3");
      SoundManager::Instance()->loadEffects();
            
      LevelData::Instance()->parseLevelList("core.xml");
      LevelData::Instance()->parseUserData();
      
      loaded = true;
    }
    
    if (animation.get_ticks() >= 3000) {
      for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
        (*sprite)->setAnimationState(ANIMATE_FADE_OUT);
      }
      
      if (!playing_music && animation.get_ticks() >= 4000) {
        SoundManager::Instance()->soundOn(false);
        playing_music = true;
      }
      
      if (animation.get_ticks() >= 5000) {
        in_loop = false;
      }
    }
  }
}