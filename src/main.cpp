// #include <GLES/gl.h>
// #include "SDL.h"
// 
// GL_API int GL_APIENTRY _dgles_load_library(void *, void *(*)(void *, const char *));
// 
// static void *proc_loader(void *h, const char *name)
// {
//     (void) h;
//     return SDL_GL_GetProcAddress(name);
// }


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
