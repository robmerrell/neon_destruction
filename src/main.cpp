#include "projection_engine/engine.h"

// scenes
#include "scenes/intro_scene.h"

int main(int argc, char* argv[]) {
  Engine engine;

  // show the title scene and start the game loop
  IntroScene *intro_scene = new IntroScene();
  engine.showScene(intro_scene);
  
  delete intro_scene;

  return 0;
}
