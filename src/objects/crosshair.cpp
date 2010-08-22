#include "crosshair.h"

CrossHair::CrossHair(float x, float y) : Sprite("", 64, 64, CROSSHAIR_TAG) {
  setX(x);
  setY(y);
  
  alpha = 1.0f;
  animation_state = ANIMATE_NONE;
}

void CrossHair::display() {
  GLfloat vertices[] = {0,64,0, 64,64,0, 0,0,0, 64,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  TexManager::Instance()->bindTexture(4);
  
  glLoadIdentity();
  glTranslatef(x - 32, y - 32, 0.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}
