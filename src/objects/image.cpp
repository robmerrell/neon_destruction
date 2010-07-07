#include "image.h"

Image::Image(float x, float y, float w, float h, int _t) : Sprite("", 64, 64, IMAGE_TAG) {
  setX(x);
  setY(y);
  
  width = w;
  height = h;
  
  texture_num = _t;
}

void Image::display() {
  GLfloat base_vertices[] = {0,height,0, width,height,0, 0,0,0, width,0,0};
  GLfloat base_tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

  glColor4f(alpha, alpha, alpha, alpha);

  TexManager::Instance()->bindTexture(texture_num);
  
  // place and rotate the turret
  glLoadIdentity();
  glTranslatef(x, y, 0.0f);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, base_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, base_tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}