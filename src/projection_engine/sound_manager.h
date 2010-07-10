#include <string>
#include <stdio.h>

#include "PDL.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "../game_const.h"

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

using namespace std;

class SoundManager {
  private:
    SoundManager();
    SoundManager(const SoundManager&);
    SoundManager& operator=(const SoundManager&);
    
    static SoundManager* inst;
    
    Mix_Music *music;
    
  public:
    static SoundManager* Instance();
    
    /**
     * Load and play the music
     */
    void loadMusic(string);
    void playMusic();
    
    /**
     * Stop all sounds and unload them
     */
    void destroyRefs();
};

#endif