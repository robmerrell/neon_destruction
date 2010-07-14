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
    
    bool loaded_effects;
    
    Mix_Music *music;
    Mix_Chunk *cannon;
    int cannon_channel;
    
    Mix_Chunk *level_end;
    int level_end_channel;
    
  public:
    static SoundManager* Instance();
    
    /**
     * Load and play the music
     */
    void loadMusic(string);
    void playMusic();
    
    /**
     * Load and play the sound effects
     */
    void loadEffects();
    void playCannon();
    void playLevelEnd();
    
    /**
     * Stop all sounds and unload them
     */
    void destroyRefs();
};

#endif