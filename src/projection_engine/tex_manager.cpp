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

void TexManager::loadTexture(string filename) {
  printf("before load\n");
  
  inst->texture[inst->texture_ref] = SOIL_load_OGL_texture
    (   
      filename.c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
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