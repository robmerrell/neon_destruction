#include "sound_manager.h"

SoundManager* SoundManager::inst = NULL; 

SoundManager::SoundManager() {
}

SoundManager* SoundManager::Instance() {
  if (!inst)
    inst = new SoundManager;
    
  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;

  Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

  return inst;
}

void SoundManager::loadMusic(string _music) {
  music = Mix_LoadMUS(_music.c_str());
}

void SoundManager::playMusic() {
  Mix_PlayMusic(music, 0);
}

void SoundManager::destroyRefs() {
  if (music != NULL) {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
  }
  
  music = NULL;
}