#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/sound_manager.h"
#include "../projection_engine/event_translations.h"

#ifndef MENU_H
#define MENU_H

class Menu : public Sprite {

  public:
    /**
     * Load the menu onto the scene
     */
    Menu();
    void destroy(cpSpace*) {};
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the platform
     */
    void display();
};

#endif