#include "SDL.h"

class Engine {

  public:
    // constructor
    Engine();
    
    // destructor
    ~Engine();
    
    // main game loop
    void loop();
    
    // replace the current scene with a new scene
    bool showScene();
  
  
  private:
    // tracks if we are running in the loop or not
    bool in_loop;
    
    // main display surface
    SDL_Surface* screen;
    
    // SDL event structure
    SDL_Event event;
};