#include "title_scene.h"

TitleScene::TitleScene() {
  quit = false;
}

TitleScene::~TitleScene() {}

bool TitleScene::setup() {
  int x, y = 0;
  srand((unsigned)time(0)); 
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    x = 1 + rand() % (SCREEN_WIDTH);
    y = 1 + rand() % (SCREEN_HEIGHT);

    starfield1[i] = cpv(x, y);
  
    x = 1 + rand() % (SCREEN_WIDTH);
    y = 1 + rand() % (SCREEN_HEIGHT);

    starfield2[i] = cpv(x, y);
  }
  
  defineStarColors();
  
  for (int i = 0; i < STARS_PER_FIELD * 2; i++) {
    starfield_sizes[i] = 1 + rand() % (2);
  }
  
  
  Image *image;

  image = new Image(0.0f, 0.0f, 512.0f, 512.0f, 17);
  addObject(image);
  
  gameLoop();
  
  delete image;
  
  return quit;
}


void TitleScene::gameLoop() {
  in_loop = true;
    
  float accumulator = 0.0f;
  int millistep = 16;
  float timeStep = float(millistep)/1000;
  fps.start();
  animation.start();
  animation_ticks = 0;
    
  while (in_loop) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // capture the events and send the relevent tap events to the game scene
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        in_loop = false;
        quit = true;
      } else if (event.type == SDL_MOUSEBUTTONUP) {
      }
    }
    
    animation_ticks = fps.get_ticks();
    
    if (animation_ticks > 32) animation_ticks = 32;
    
    accumulator += animation_ticks;
    fps.start();
    
    while (accumulator >= millistep) {
      accumulator -= millistep;
    }
    
    glDisable(GL_BLEND);
    
    // draw the background
    // moveBackground(animation_ticks);
    updateAnimation(animation_ticks);
    // drawBackground();
    
    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

    // display
    vector<Sprite*>::iterator sprite;
    for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
      (*sprite)->display();
    }
    
    // update the screen
    SDL_GL_SwapBuffers();
    
    if (animation.get_ticks() >= 3000) {
      for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
        (*sprite)->setAnimationState(ANIMATE_FADE_OUT);
      }
      
      if (animation.get_ticks() >= 5000) {
        in_loop = false;
      }
    }
  }
}

void TitleScene::drawBackground() {
  TexManager::Instance()->unbindTexture();

  int v_count = 0;

  GLfloat star_verts[STARS_PER_FIELD * 4];
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    star_verts[v_count] = starfield1[i].x;
    v_count++;

    star_verts[v_count] = starfield1[i].y;
    v_count++;

    star_verts[v_count] = starfield2[i].x;
    v_count++;

    star_verts[v_count] = starfield2[i].y;
    v_count++;
  }

  glLoadIdentity();
  glTranslatef(0, 0, 0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_POINT_SIZE_ARRAY_OES);
  
  glVertexPointer(2, GL_FLOAT, 0, star_verts);
  glColorPointer(4, GL_FLOAT, 0, starfield_colors);
  glPointSizePointerOES(GL_FLOAT, 0, starfield_sizes);
  glDrawArrays(GL_POINTS, 0, STARS_PER_FIELD * 2);
  
  glDisableClientState(GL_POINT_SIZE_ARRAY_OES);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void TitleScene::moveBackground(int ticks) {
  for (int i = 0; i < STARS_PER_FIELD; i++) {
    starfield1[i].x -= (STAR_FIELD1_SPEED * (ticks * 0.001));
    starfield2[i].x -= (STAR_FIELD2_SPEED * (ticks * 0.001));

    if (starfield1[i].x < 0)
      starfield1[i].x = SCREEN_WIDTH;
    if (starfield2[i].x < 0)
      starfield2[i].x = SCREEN_WIDTH;
  }
}

void TitleScene::defineStarColors() {
  int random_num, color_index = 0;
  float r,g,b = 1.0f;
  for (int i = 0; i < STARS_PER_FIELD*2; i++) {
    random_num = 1 + rand() % (10);

    // yellow
    if (random_num == 1) {
      r = 1.0f;
      g = 0.99f;
      b = 0.94f;
    }
    // blue
    else if (random_num == 2) { 
      r = 0.9f;
      g = 0.99f;
      b = 1.0f;
    }
    // red
    else if (random_num == 3) {
      r = 1.0f;
      g = 0.9f;
      b = 0.9f;
    }
    // white
    else {
      r = 1.0f;
      g = 1.0f;
      b = 1.0f;
    }
    
    starfield_colors[color_index] = r;
    starfield_colors[color_index + 1] = g;
    starfield_colors[color_index + 2] = b;
    starfield_colors[color_index + 3] = 1.0f;
    
    color_index += 4;
  }
}