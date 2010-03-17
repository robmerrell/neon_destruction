#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  // add the logo image
  // add the logo mask
  logo = new Sprite("", 64, 64);
  logo->setX(100);
  logo->setY(100);
  addObject(logo);

  // setup the physics environment
  worldAABB.lowerBound.Set(0, 0);
  worldAABB.upperBound.Set(640/PTM_RATIO, 480/PTM_RATIO);
  
  b2Vec2 gravity(0.0f, 10.0f);
  bool doSleep = true;
  
  world = new b2World(worldAABB, gravity, doSleep);
  
  b2BodyDef bodyDef;
  bodyDef.position.Set(p2m(300), p2m(100));
  body = world->CreateBody(&bodyDef);
  
  b2PolygonDef shapeDef;
  shapeDef.SetAsBox(1.0f, 1.0f);
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.3f;
  shapeDef.restitution = 2.0f;
  body->CreateShape(&shapeDef);
  body->SetMassFromShapes();

  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  float32 timeStep = 1.0f / 60.0f;
  int32 iterations = 10;
  
  world->Step(timeStep, iterations);
  b2Vec2 position = body->GetPosition();
  float32 angle = body->GetAngle();
  
  logo->setX(m2p(position.x));
  logo->setY(m2p(position.y));
}

