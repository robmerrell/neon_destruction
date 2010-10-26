#include "level_dialog.h"
#include <iostream>
#include <sstream>

using namespace std;

LevelDialog::LevelDialog() : Sprite("", 64, 64, LEVEL_DIALOG_TAG) {
  show_star1 = false;
  show_star2 = false;
  show_star3 = false;  
  
  star1_begin_fade = false;
  star1_end_fade = false;
}

void LevelDialog::display() {
  float x = 32.0f;
  float y = 0.0f;
  
  // coordinates for texture
  float x1 = 16.0f;
  float y1 = 11.0f;
  float x2 = 435.0f;
  float y2 = 340.0f;
  
  float length = y2-y1;
  float bottom_length = x2-x1;
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
  TexManager::Instance()->bindTexture(20);

  GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
  GLfloat tex_back[] = {x1/512.0f,y2/512.0f,0, x2/512.0f,y2/512.0f,0, x1/512.0f,y1/512.0f,0, x2/512.0f,y1/512.0f,0};

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
  if (show_star1) {
    glLoadIdentity();
    glTranslatef(140.0f, 30.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, star_vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
  
  // star 2
  if (show_star2) {
    glLoadIdentity();
    glTranslatef(208.0f, 30.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, star_vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
  
  // star 3
  if (show_star3) {
    glLoadIdentity();
    glTranslatef(278.0f, 30.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, star_vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, star_tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
  
  // message
  TextureString *tx = new TextureString(message_x, message_y, message);
  tx->display();
  delete tx;
  
  // shots
  string shots_str = "Shots: ";
  stringstream ss;
  ss << shots;
  shots_str.append(ss.str());
  
  tx = new TextureString(63.0f, 190.0f, shots_str);
  tx->display();
  delete tx;
  
  // time
  if (timer > 0) {
    string timer_str = "Time: ";
    timer_str.append(elapsed);
    timer_str.append("s");
    
    tx = new TextureString(74.0f, 170.0f, timer_str);
    tx->display();
    delete tx;
  }
  
  // best
  string best_str = "Best: ";
  best_str.append(LevelData::Instance()->getCurrentDetails().score);
  
  tx = new TextureString(302.0f, 190.0f, best_str);
  tx->display();
  delete tx;
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void LevelDialog::setStarData(int s1, int s2, int s3, string s_type) {
  star1 = s1;
  star2 = s2;
  star3 = s3;
  star_type = s_type;
}

void LevelDialog::setTimerData(int s1, int s2, int s3) {
  time1 = s1;
  time2 = s2;
  time3 = s3;
}

void LevelDialog::setScoreData(int _shots, int _timer, string _elapsed) {
  shots = _shots;
  timer = _timer;
  elapsed = _elapsed;
  
  show_star1 = false;
  show_star2 = false;
  show_star3 = false;
  
  // determine which stars we should show
  if (star_type == "shots") {
    if (shots <= star1) show_star1 = true;
    if (shots <= star2) show_star2 = true;
    if (shots <= star3) show_star3 = true;
  } else if (star_type == "timer") {
    if (shots <= star1 && timer <= time1) show_star1 = true;
    if (shots <= star2 && timer <= time2) show_star2 = true;
    if (shots <= star3 && timer <= time3) show_star3 = true;
  }

  message_y = 130.0f;
  
  // 3 stars
  if (show_star3) {
    int index = rand() % 4;
  
    switch(index) {
      case 1:
        message = "Woohoo!";
        message_x = 195.0f;
        break;

      case 2:
        message = "You are so S-M-R-T";
        message_x = 132.0f;
        break;

      default:
        message = "Your mom must be proud";
        message_x = 113.0f;
        break;
    }
  }
  
  
  // 2 stars
  if (show_star2 && !show_star3) {
    int index = rand() % 4;

    switch(index) {
      case 1:
        message = "So close";
        message_x = 185.0f;
        break;

      case 2:
        message = "Not bad";
        message_x = 195.0f;
        break;

      default:
        message = "You can do it!";
        message_x = 155.0f;
        break;
    }
  }


  // 1 star
  if (show_star1 && !show_star2 && !show_star3) {
    int index = rand() % 4;
    
    switch(index) {
      case 1:
        message = "meh";
        message_x = 210.0f;
        break;

      case 2:
        message = "Give it another try";
        message_x = 125.0f;
        break;

      default:
        message = "Getting better";
        message_x = 155.0f;
        break;
    }
  }
  
  
  // 0 stars
  if (!show_star1 && !show_star2 && !show_star3) {
    int index = rand() % 5;
    
    switch(index) {
      case 1:
        message = "Boooooooooooooo!";
        message_x = 145.0f;
        break;

      case 2:
        message = "What was that all about?";
        message_x = 100.0f;
        break;
        
      case 3:
        message = "At least it can't get any worse";
        message_x = 60.0f;
        break;

      default:
        message = "Lame";
        message_x = 210.0f;
        break;
    }
  }
}

int LevelDialog::getStarCount() {
  int stars = 0;
  
  if (show_star1) stars += 1;
  if (show_star2) stars += 1;
  if (show_star3) stars += 1;
  
  return stars;
}