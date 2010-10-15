#include "../projection_engine/sprite.h"
#include "../game_const.h"
#include "../projection_engine/tex_manager.h"
#include "../projection_engine/sound_manager.h"
#include "../projection_engine/event_translations.h"
#include "../objects/texture_string.h"
#include "../objects/image.h"
#include "../projection_engine/level_data.h"

#ifndef LEVEL_DIALOG_H
#define LEVEL_DIALOG_H

class LevelDialog : public Sprite {

  private:
    int star1;
    int star2;
    int star3;
    int time1;
    int time2;
    int time3;
    string star_type;
    
    int shots;
    int timer;
    string elapsed;
    
    bool show_star1;
    bool show_star2;
    bool show_star3;
    
    bool star1_begin_fade;
    bool star1_end_fade;
    
    string message;
    float message_x;
    float message_y;

  public:
    /**
     * Load the Dialog onto the scene
     */
    LevelDialog();
    
    void destroy(cpSpace*) {};
    void definePhysics(cpSpace*) {};
    
    /**
     * star1, star2, star3, star_type
     */
    void setStarData(int, int, int, string);
    
    /**
     * star1, star2, star3
     */
    void setTimerData(int, int, int);
    
    /**
     * shots, timer, elapsed
     */
    void setScoreData(int, int, string);
    
    int getStarCount();
    
    /**
     * Display the dialog
     */
    void display();
};

#endif