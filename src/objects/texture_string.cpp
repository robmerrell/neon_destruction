#include "texture_string.h"

TextureString::TextureString(float x, float y, string _m) : Sprite("", 64, 64, TEXTURE_STRING_TAG) {
  setX(x);
  setY(y);
  message = _m;
  use_large = false;
  
  r = 1.0f;
  g = 1.0f;
  b = 1.0f;
}

void TextureString::setMessage(string m) {
  message = m;
}

void TextureString::useLarge() {
  use_large = true;
}

void TextureString::color(float _r, float _g, float _b) {
  r = _r;
  g = _g;
  b = _b;
}

void TextureString::display() {
  float font_width;
  float font_height;
  float tex_size;
  
  if (use_large) {
    TexManager::Instance()->bindTexture(21);
    font_width = LARGE_FONT_WIDTH;
    font_height = LARGE_FONT_HEIGHT;
    tex_size = 512.0f;
  } else {
    TexManager::Instance()->bindTexture(11);
    font_width = SMALL_FONT_WIDTH;
    font_height = SMALL_FONT_HEIGHT;
    tex_size = 256.0f;
  }
  
  GLfloat vertices[] = {0,font_height,0, font_width,font_height,0, 0,0,0, font_width,0,0};

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glLoadIdentity();
  glTranslatef(x, y, 0.0);
  
  glColor4f(r, g, b, alpha);
    
  for (int i = 0; i < message.size(); i++) {
    int ind = int(message[i]) - 32;
    
    float left;
    float top;
    
    if (use_large) {
      left = (float)LARGE_FONTMAP[ind].x;
      top = (float)LARGE_FONTMAP[ind].y;
    } else {
      left = (float)FONTMAP[ind].x;
      top = (float)FONTMAP[ind].y; 
    }
    
    float right = (left + font_width) / tex_size;
    float bottom = (top + font_height) / tex_size;
    
    left /= tex_size;
    top /= tex_size;
    
    GLfloat tex[] = {left,bottom,0, right,bottom,0, left,top,0, right,top,0};
    
    glTranslatef(font_width, 0.0f, 0.0f);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, tex);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}
