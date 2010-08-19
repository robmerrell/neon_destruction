#include "projection_engine/engine.h"
#include "projection_engine/tex_manager.h"
#include "projection_engine/sound_manager.h"
#include "projection_engine/level_data.h"
#include "scenes/gameplay_scene.h"
#include "scenes/title_scene.h"
#include "scenes/thank_you_scene.h"

int main(int argc, char* argv[]) {
  Engine engine(false);
  
  // turn off banners
  PDL_BannerMessagesEnable(PDL_FALSE);
  
  // loading screen texture
  TexManager::Instance()->loadTexture("assets/loading.png", true);

  // show the title scene and start the game loop
  TitleScene *title_scene = new TitleScene();
  bool quit = engine.showScene(title_scene);
  // delete title_scene;
  
  if (!quit) {
    GameplayScene *gameplay_scene = new GameplayScene();
    quit = engine.showScene(gameplay_scene);
    delete gameplay_scene;
  }
  
  if (!quit) {
    ThankYouScene *thank_you_scene = new ThankYouScene();
    engine.showScene(thank_you_scene);
    // delete thank_you_scene;
  }
  
  return 0;
}
