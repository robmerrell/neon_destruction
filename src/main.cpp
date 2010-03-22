#include "projection_engine/engine.h"

// scenes
#include "scenes/test_scene.h"

int main(int argc, char* argv[]) {
  Engine engine(true);

  // show the title scene and start the game loop
  TestScene *test_scene = new TestScene();
  engine.showScene(test_scene);
  
  delete test_scene;

  return 0;
}
