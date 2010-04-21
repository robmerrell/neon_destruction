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
    TexManager();
    TexManager(const TexManager&);
    TexManager& operator=(const TexManager&);
    
    static TexManager* inst;
    
    GLuint texture[TEXTURE_COUNT];
    int texture_ref;
    
  public:
    static TexManager* Instance();
    
    /**
     * Load the specified texture
     */
    void loadTexture(string filename);
    
    /**
     * Bind the referenced texture
     */
    void bindTexture(int);
    
    /**
     * Unbind a texture
     */
    void unbindTexture();
    
    /**
     * Return the current texture refernce count
     */
    int getTextureRef();
    
};

#endif