#include "tex_manager.h"

TexManager* TexManager::inst = NULL; 

TexManager::TexManager() {
  texture_ref = 0;
}

TexManager* TexManager::Instance() {
  if (!inst)
    inst = new TexManager;
  
  // glGenTextures(TEXTURE_COUNT, inst->texture);
    
  return inst;
}

void TexManager::loadTexture(string filename, bool alpha) {
  unsigned int flags = SOIL_FLAG_MIPMAPS;
  if (alpha)
    flags = flags | SOIL_FLAG_MULTIPLY_ALPHA;
    
  #ifdef DEVICE
    char app_dir[256];
    PDL_GetCallingPath(app_dir, 256);
    string full_path(app_dir);
    full_path.append(filename);
  #else
    string full_path = filename;
  #endif
  
  inst->texture[inst->texture_ref] = SOIL_load_OGL_texture
    (   
      full_path.c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      flags
    );
    
  if (inst->texture[inst->texture_ref] == 0) {
    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
  } else {
    printf("loaded\n");
  }
    
  inst->texture_ref++;
}

void TexManager::bindTexture(int ref) {
  glBindTexture(GL_TEXTURE_2D, inst->texture[ref]);
}

void TexManager::unbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

int TexManager::getTextureRef() {
  return inst->texture_ref;
}

void TexManager::deleteAllTextures() {
  glDeleteTextures(TEXTURE_COUNT, inst->texture);
}