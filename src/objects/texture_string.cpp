#include "texture_string.h"

TextureString::TextureString(float x, float y, string _m) : Sprite("", 64, 64, TEXTURE_STRING_TAG) {
  setX(x);
  setY(y);
  message = _m;
  
  r = 1.0f;
  g = 1.0f;
  b = 1.0f;
}

void TextureString::setMessage(string m) {
  message = m;
}

void TextureString::color(float _r, float _g, float _b) {
  r = _r;
  g = _g;
  b = _b;
}

void TextureString::display() {
  TexManager::Instance()->bindTexture(11);
  
  GLfloat vertices[] = {0,18,0, 11,18,0, 0,0,0, 11,0,0};

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glLoadIdentity();
  glTranslatef(x, y, 0.0);
  
  glColor4f(r, g, b, alpha);
    
  for (int i = 0; i < message.size(); i++) {
    int ind = int(message[i]) - 32;
    
    float left = (float)FONTMAP[ind].x;
    float top = (float)FONTMAP[ind].y;
    
    float right = (left + 11.0f) / 256.0f;
    float bottom = (top + 18.0f) / 256.0f;
    
    left /= 256.0f;
    top /= 256.0f;
    
    GLfloat tex[] = {left,bottom,0, right,bottom,0, left,top,0, right,top,0};
    
    glTranslatef(11.0f, 0.0f, 0.0f);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, tex);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}
