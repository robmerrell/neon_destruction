#include "level_dialog.h"
#include <iostream>
#include <sstream>

using namespace std;

LevelDialog::LevelDialog() : Sprite("", 64, 64, LEVEL_DIALOG_TAG) {  
}

void LevelDialog::display() {
  float x = 48.0f;
  float y = 10.0f;
  
  float length = 300.0f;
  float bottom_length = 384.0f;
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
  TexManager::Instance()->bindTexture(20);

  GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
  GLfloat tex_back[] = {0,length/512.0f,0, bottom_length/512.0f,length/512.0f,0, 0,0,0, bottom_length/512.0f,0,0};

  glLoadIdentity();
  glColor4f(1.0f, 1.0f, 1.0f, alpha);
  glTranslatef(x, y, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_back);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_back);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


  // stars  
  GLfloat star_vertices[] = {0,64,0, 64,64,0, 0,0,0, 64,0,0};
  GLfloat star_tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  TexManager::Instance()->bindTexture(19);
  
  // star 1
  glLoadIdentity();
  glTranslatef(130.0f, 30.0f, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, star_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  // star 2
  glLoadIdentity();
  glTranslatef(205.0f, 30.0f, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, star_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  // star 3
  glLoadIdentity();
  glTranslatef(280.0f, 30.0f, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, star_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  // message
  TextureString *tx = new TextureString(80.0f, 110.0f, "Boooooooooooooooo!");
  tx->display();
  delete tx;
  
  // shots
  tx = new TextureString(60.0f, 170.0f, "Shots: 100");
  tx->display();
  delete tx;
  
  // best
  tx = new TextureString(320.0f, 170.0f, "Best: 8");
  tx->display();
  delete tx;

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
