#include <string>
#include <stdio.h>

#include "GLES/gl.h"
#include "../soil/SOIL.h"
#include "../game_const.h"

#ifndef TEX_MANAGER_H
#define TEX_MANAGER_H

using namespace std;

class TexManager {
  private:
    TexManager() {};
    TexManager(const TexManager&);
    TexManager& operator=(const TexManager&);
    
    static TexManager* inst;
    
    GLuint texture;
    int texture_ref;
    
  public:
    static TexManager* Instance();
    
    void loadTexture(string filename);
    void bindTexture(int);
    void unbindTexture();
    int getTextureRef();
    
};

#endif