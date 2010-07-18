#include "projection_engine/engine.h"
#include "projection_engine/tex_manager.h"
#include "projection_engine/sound_manager.h"
#include "scenes/gameplay_scene.h"
#include "scenes/title_scene.h"

int main(int argc, char* argv[]) {
  Engine engine(false);
  
  // load the textures
  TexManager::Instance()->loadTexture("assets/ball.png", true);
  TexManager::Instance()->loadTexture("assets/ball.png", true); // TODO: remove me
  TexManager::Instance()->loadTexture("assets/star_background.png", false); // TODO: remove me
  TexManager::Instance()->loadTexture("assets/cannon_top.png", true);
  TexManager::Instance()->loadTexture("assets/cannon_top_glow.png", true);
  TexManager::Instance()->loadTexture("assets/cannon_base.png", true);
  TexManager::Instance()->loadTexture("assets/platform.png", true);
  TexManager::Instance()->loadTexture("assets/line_cap.png", true);
  TexManager::Instance()->loadTexture("assets/white.png", true); // TODO: remove me
  TexManager::Instance()->loadTexture("assets/crosshairs.png", true);
  TexManager::Instance()->loadTexture("assets/circle.png", true);
  TexManager::Instance()->loadTexture("assets/triangle.png", true);
  TexManager::Instance()->loadTexture("assets/particle.png", true);
  TexManager::Instance()->loadTexture("assets/blue_platform_atlas.png", true);
  TexManager::Instance()->loadTexture("assets/green_platform_atlas.png", true);
  TexManager::Instance()->loadTexture("assets/goal.png", true);
  TexManager::Instance()->loadTexture("assets/gravity_switch.png", true);
  TexManager::Instance()->loadTexture("assets/loading.png", true);
  TexManager::Instance()->loadTexture("assets/font.png", true);
  TexManager::Instance()->loadTexture("assets/menu.png", true);
  TexManager::Instance()->loadTexture("assets/sound_highlight.png", true);
  TexManager::Instance()->loadTexture("assets/go_to_level.png", true);
  
  SoundManager::Instance()->loadMusic("assets/music.mp3");
  SoundManager::Instance()->loadEffects();
  SoundManager::Instance()->soundOn(true);
  SoundManager::Instance()->playMusic();

  // show the title scene and start the game loop
  // TitleScene *title_scene = new TitleScene();
  // bool quit = engine.showScene(title_scene);
  // delete title_scene;
  
  bool quit = false;
  
  if (!quit) {
    GameplayScene *gameplay_scene = new GameplayScene();
    engine.showScene(gameplay_scene);
    delete gameplay_scene;
  }
  
  return 0;
}
