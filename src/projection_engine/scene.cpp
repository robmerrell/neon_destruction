#include "scene.h"

using namespace std;

// TODO: check this for memory leaks
Scene::~Scene() {
  // free all of the sprites
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
}

void Scene::addObject(Sprite* sprite) {
  objects.push_back(sprite);
}

Sprite* Scene::findObject(int tag) {
  vector<Sprite*>::iterator sprite;
  for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
    if ((*sprite)->getTag() == tag) {
      return *sprite;
    }
  }
  
  return NULL;
}

void Scene::setDrawPhysics(bool draw) {
  draw_physics = draw;
}

void Scene::updateAnimation(int ticks) {
  vector<Sprite*>::iterator sprite;
  float val = 0.0f;
  
  for (sprite = objects.begin(); sprite != objects.end(); sprite++) {
    
    if ((*sprite)->getAnimationState() == ANIMATE_FADE_IN) {
      val = (*sprite)->getAlpha() + (ANIMATE_FADE_SPEED * (ticks * 0.001));
      (*sprite)->setAlpha(val);
      
      if (val >= 1.0f) {
        (*sprite)->setAnimationState(ANIMATE_NONE);
      }
    } else if ((*sprite)->getAnimationState() == ANIMATE_FADE_OUT) {
      val = (*sprite)->getAlpha() - (ANIMATE_FADE_SPEED * (ticks * 0.001));
      (*sprite)->setAlpha(val);
      
      if (val <= 0.0f) {
        (*sprite)->setAnimationState(ANIMATE_NONE);
      }
    }
  }
}
