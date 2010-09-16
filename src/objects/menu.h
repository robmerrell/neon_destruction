#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/sound_manager.h"
#include "../projection_engine/event_translations.h"
#include "../objects/texture_string.h"
#include "../projection_engine/level_data.h"
#include <math.h>

#ifndef MENU_H
#define MENU_H

class Menu : public Sprite {

  private:
    bool level_picker;
    int page;

  public:
    /**
     * Load the menu onto the scene
     */
    Menu();
    void destroy(cpSpace*) {};
    void definePhysics(cpSpace*) {};
    
    void setLevelPicker(bool);
    bool getLevelPicker();
    
    void nextPage();
    void prevPage();
    int getPage();
    void setPage();
    
    /**
     * Display the platform
     */
    void display();
};

#endif