#ifndef SCENE_H
#define SCENE_H

class Scene {

  protected:
    bool in_loop;
  
  public:
    /**
     * Constructor
     */
    Scene();
    
    /**
     * Handle setup of game objects for the scene in preparation for the game loop
     */
   virtual void setup() {};
    
    /**
     * Schedules a loop that calls the param method every count seconds
     *
     */
    void scheduleLoop();
  
};

#endif