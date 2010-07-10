#include "sound_manager.h"

SoundManager* SoundManager::inst = NULL; 

SoundManager::SoundManager() {
  // cannon_channel = -1;
  // loaded_effects = false;
}

SoundManager* SoundManager::Instance() {
  if (!inst) {
    inst = new SoundManager;
    
    inst->cannon_channel = -1;
    inst->loaded_effects = false;
    
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 2048;

    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
  }
    
  return inst;
}

void SoundManager::loadMusic(string _music) {
  music = Mix_LoadMUS(_music.c_str());
}

void SoundManager::loadEffects() {
  cannon = Mix_LoadWAV("assets/cannon.wav");
  if(cannon == NULL) {
  	fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
  }
  loaded_effects = true;
}

void SoundManager::playMusic() {
  Mix_PlayMusic(music, -1);
}

void SoundManager::playCannon() {
  cannon_channel = Mix_PlayChannel(-1, cannon, 0);
}

void SoundManager::destroyRefs() {
  if (music != NULL) {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
  }
  
  if (loaded_effects) {
    Mix_HaltChannel(cannon_channel);
  }
  
  music = NULL;
}