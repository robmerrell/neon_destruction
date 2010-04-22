#include "projection_engine/engine.h"
#include "projection_engine/tex_manager.h"

// scenes
#include "scenes/test_scene.h"

int main(int argc, char* argv[]) {
  Engine engine(false);
  
  // load the textures
  TexManager::Instance()->loadTexture("assets/ball.png", true);
  TexManager::Instance()->loadTexture("assets/ball_glow.png", true);
  TexManager::Instance()->loadTexture("assets/star_background.png", false);

  // show the title scene and start the game loop
  TestScene *test_scene = new TestScene();
  engine.showScene(test_scene);
  
  delete test_scene;

  return 0;
}
