#include "tex_manager.h"

TexManager* TexManager::inst = NULL; 

TexManager* TexManager::Instance() {
  if (!inst)
    inst = new TexManager;
    
  return inst;
}

void TexManager::loadTexture(string filename) {
  glGenTextures(1, &inst->texture);
  
  inst->texture = SOIL_load_OGL_texture
    (   
      "assets/ball.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
  if (inst->texture == 0) {
    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
  } else {
    printf("loaded\n");
  }
    
  inst->texture_ref=27;
}

void TexManager::bindTexture(int ref) {
  glBindTexture(GL_TEXTURE_2D, inst->texture);
}

void TexManager::unbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

int TexManager::getTextureRef() {
  return inst->texture_ref;
}