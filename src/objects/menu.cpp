#include "menu.h"
#include <iostream>

Menu::Menu() : Sprite("", 64, 64, MENU_TAG) {  
}

void Menu::display() {
  float x = 48.0f;
  float y = 10.0f;
  
  float length = 300.0f;
  float bottom_length = 384.0f;
  
  // draw the border
  int ti = 8;
  GLfloat vertices[] = {0,25.0f,0, length,25.0f,0, 0,0,0, length,0,0};
  GLfloat tex[] = {0,PLATFORM_BOTTOM[ti],0, PLATFORM_RIGHT[ti],PLATFORM_BOTTOM[ti],0, 0,PLATFORM_TOP[ti],0, PLATFORM_RIGHT[ti],PLATFORM_TOP[ti],0};  
  
  int bi = 9;
  GLfloat vertices_hor[] = {0,25.0f,0, bottom_length,25.0f,0, 0,0,0, bottom_length,0,0};
  GLfloat tex_hor[] = {0,PLATFORM_BOTTOM[bi],0, PLATFORM_RIGHT[bi],PLATFORM_BOTTOM[bi],0, 0,PLATFORM_TOP[bi],0, PLATFORM_RIGHT[bi],PLATFORM_TOP[bi],0};
  
  TexManager::Instance()->bindTexture(13);
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   
  TexManager::Instance()->bindTexture(19);

  GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
  GLfloat tex_back[] = {0,length/512.0f,0, bottom_length/512.0f,length/512.0f,0, 0,0,0, bottom_length/512.0f,0,0};
  
  glDisable(GL_BLEND);  
  glLoadIdentity();
  glColor4f(1.0f, 1.0f, 1.0f, alpha);
  glTranslatef(x, y, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_back);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_back);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glEnable(GL_BLEND);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}