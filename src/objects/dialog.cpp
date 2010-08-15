#include "Dialog.h"
#include <iostream>
#include <sstream>

using namespace std;

Dialog::Dialog(string level) : Sprite("", 64, 64, DIALOG_TAG) {  
  level_id = level;
}

void Dialog::display() {
  float x = 48.0f;
  float y = 10.0f;
  
  float length = 300.0f;
  float bottom_length = 384.0f;
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
  TexManager::Instance()->bindTexture(14);

  GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
  GLfloat tex_back[] = {0,length/512.0f,0, bottom_length/512.0f,length/512.0f,0, 0,0,0, bottom_length/512.0f,0,0};

  glLoadIdentity();
  glColor4f(1.0f, 1.0f, 1.0f, alpha);
  glTranslatef(x, y, 0.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_back);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_back);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  if (level_id == "1") {
    TextureString *tx = new TextureString(80.0f, 30.0f, "Tap to shoot the cannon.");
    tx->display();
    
    tx = new TextureString(80.0f, 55.0f, "Hit the target using as few");
    tx->display();
    
    tx = new TextureString(80.0f, 80.0f, "shots as possible.");
    tx->display();
    
    tx = new TextureString(80.0f, 150.0f, "The farther away you tap");
    tx->display();
    
    tx = new TextureString(80.0f, 175.0f, "from the cannon, the stronger");
    tx->display();
    
    tx = new TextureString(80.0f, 200.0f, "your shot will be.");
    tx->display();
  } else if (level_id == "2") {
    TextureString *tx = new TextureString(80.0f, 30.0f, "You can move green shapes");
    tx->display();
    
    tx = new TextureString(80.0f, 55.0f, "by shooting them.");
    tx->display();
    
    tx = new TextureString(80.0f, 100.0f, "Blue shapes are stuck. You");
    tx->display();
    
    tx = new TextureString(80.0f, 125.0f, "can't move them no matter");
    tx->display();
    
    tx = new TextureString(80.0f, 150.0f, "how hard you try.");
    tx->display();
  } else if (level_id == "8") {
    TextureString *tx = new TextureString(80.0f, 30.0f, "Sometimes you get yourself");
    tx->display();
    
    tx = new TextureString(80.0f, 55.0f, "into a situation that");
    tx->display();
    
    tx = new TextureString(80.0f, 80.0f, "you can't fix.");
    tx->display();
    
    tx = new TextureString(80.0f, 150.0f, "Slide down on the gesture");
    tx->display();
    
    tx = new TextureString(80.0f, 175.0f, "area and tap 'restart level'.");
    tx->display();
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
