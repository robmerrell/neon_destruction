#include "projection_engine/engine.h"

int main(int argc, char* argv[]) {
  Engine engine;

  // show the title scene and start the game loop
  engine.showScene();
  engine.loop();
  
  return 0;
}
