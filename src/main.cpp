#include "projection_engine/engine.h"
#include "projection_engine/tex_manager.h"
#include "levels.h"

int main(int argc, char* argv[]) {
  Engine engine(false);
  
  // load the textures
  TexManager::Instance()->loadTexture("assets/ball.png", true);
  TexManager::Instance()->loadTexture("assets/ball.png", true); // TODO: remove me
  TexManager::Instance()->loadTexture("assets/star_background.png", false);
  TexManager::Instance()->loadTexture("assets/cannon_top.png", true);
  TexManager::Instance()->loadTexture("assets/cannon_top_glow.png", true);
  TexManager::Instance()->loadTexture("assets/cannon_base.png", true);
  TexManager::Instance()->loadTexture("assets/platform.png", true);
  TexManager::Instance()->loadTexture("assets/line_cap.png", true);
  TexManager::Instance()->loadTexture("assets/white.png", true);

  // show the title scene and start the game loop
  BoxTumble *box_tumble = new BoxTumble();
  engine.showScene(box_tumble);
  
  delete box_tumble;

  return 0;
}
