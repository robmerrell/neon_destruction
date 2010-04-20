#include "projection_engine/engine.h"
#include "projection_engine/tex_manager.h"

// scenes
#include "scenes/test_scene.h"

int main(int argc, char* argv[]) {
  Engine engine(false);
  
  // load the textures
  TexManager::Instance()->loadTexture("filename");

  // show the title scene and start the game loop
  TestScene *test_scene = new TestScene();
  engine.showScene(test_scene);
  
  delete test_scene;

  return 0;
}
