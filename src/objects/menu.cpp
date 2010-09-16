#include "menu.h"
#include <iostream>
#include <sstream>

using namespace std;

Menu::Menu() : Sprite("", 64, 64, MENU_TAG) {  
  level_picker = false;
  page = 0;
}

bool Menu::getLevelPicker() {
  return level_picker;
}

void Menu::setLevelPicker(bool _lp) {
  level_picker = _lp;
}

int Menu::getPage() {
  return page;
}

void Menu::prevPage() {
  if (page >= 1)
    page--;
}

void Menu::nextPage() {
  if ((page+1)*3 <= LevelData::Instance()->getCoreLevelCount())
    page++;
}

void Menu::setPage() {
  int placement = LevelData::Instance()->getCurrentLevelPlacement();
  page = (int)ceil((float)placement / (float)3) - 1;
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
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   
  if (!level_picker) {
    TexManager::Instance()->bindTexture(12);

    GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
    GLfloat tex_back[] = {0,length/512.0f,0, bottom_length/512.0f,length/512.0f,0, 0,0,0, bottom_length/512.0f,0,0};
  
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glTranslatef(x, y, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, vertices_back);
    glTexCoordPointer(3, GL_FLOAT, 0, tex_back);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
    GLfloat sound_vertices[] = {0,64,0, 64,64,0, 0,0,0, 64,0,0};
    GLfloat sound_tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};

    TexManager::Instance()->bindTexture(13);
  
    glLoadIdentity();
    if (SoundManager::Instance()->soundOn())
      glTranslatef(206.0f, 126.0f, 0.0f);
    else
      glTranslatef(318.0f, 126.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, sound_vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, sound_tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  } else {
    TexManager::Instance()->bindTexture(14);

    GLfloat vertices_back[] = {0,length,0, bottom_length,length,0, 0,0,0, bottom_length,0,0};
    GLfloat tex_back[] = {0,length/512.0f,0, bottom_length/512.0f,length/512.0f,0, 0,0,0, bottom_length/512.0f,0,0};
  
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glTranslatef(x, y, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, vertices_back);
    glTexCoordPointer(3, GL_FLOAT, 0, tex_back);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


    TexManager::Instance()->bindTexture(10);
    GLfloat vertices_prev[] = {0,48,0, 48,48,0, 0,0,0, 48,0,0};
    GLfloat tex_prev[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
    
    // previous
    if (page >= 1) {
      glLoadIdentity();
      glTranslatef(20.0f, 285.0f, 0.0);

      glTranslatef(48.0f/2, -48.0f/2, 0.0);
      glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-48.0f/2, 48.0f/2, 0.0);

      glVertexPointer(3, GL_FLOAT, 0, vertices_prev);
      glTexCoordPointer(3, GL_FLOAT, 0, tex_prev);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    
    // next
    if ((page+1)*3 <= LevelData::Instance()->getCoreLevelCount()) {
      glLoadIdentity();
      glTranslatef(396.0f, 285.0f, 0.0);

      glTranslatef(48.0f/2, -48.0f/2, 0.0);
      glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-48.0f/2, 48.0f/2, 0.0);
    
      glVertexPointer(3, GL_FLOAT, 0, vertices_prev);
      glTexCoordPointer(3, GL_FLOAT, 0, tex_prev);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    int count = 0;
    for (int i = 3*page; i < 3*page + 3; i++) {
      if (i < LevelData::Instance()->getCoreLevelCount()) {
        LevelDetails level = LevelData::Instance()->getDetailsByPosition(i+1);
        
        bool can_show = false;
        if (level.completed == "1") can_show = true;
        if (i != 0) {
          LevelDetails prev_level = LevelData::Instance()->getDetailsByPosition(i);
          if (prev_level.completed == "1") can_show = true;
        }
        
        stringstream name;
        string final_name;
        name << i+1 << "." << level.name;
        
        if (!can_show)
          name << "(N/A)";
        
        final_name = name.str();
        
        string score = "Best score: ";
        score.append(level.score);
        
        TextureString *tx = new TextureString(50.0f, 20.0f + count*65.0f, final_name);
        if (!can_show) tx->color(0.5f, 0.5f, 0.5f);
        tx->display();
        
        tx = new TextureString(50.0f, 20.0f + count*65.0f + 16.0f, score);
        if (!can_show) tx->color(0.5f, 0.5f, 0.5f);
        tx->display();
        count++;
      }
    }
  }
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}