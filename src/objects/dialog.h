#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/sound_manager.h"
#include "../projection_engine/event_translations.h"
#include "../objects/texture_string.h"
#include "../projection_engine/level_data.h"

#ifndef DIALOG_H
#define DIALOG_H

class Dialog : public Sprite {

  private:
    string level_id;

  public:
    /**
     * Load the Dialog onto the scene
     */
    Dialog(string);
    void destroy(cpSpace*) {};
    void definePhysics(cpSpace*) {};
    
    /**
     * Display the platform
     */
    void display();
};

#endif