#include "intro_scene.h"

#include <iostream>

void IntroScene::setup() {
  // add the logo image
  // add the logo mask
  logo = new Sprite("", 64, 64);
  logo->setX(100);
  logo->setY(100);
  addObject(logo);
  
  
  // Add a moving circle object.
	cpFloat radius = 15.0f;
	cpFloat mass = 10.0f;
	// This time we need to give a mass and moment of inertia when creating the circle.
	cpBody *ballBody = cpBodyNew(mass, cpMomentForCircle(mass, 0.0f, radius, cpvzero));
	// Set some parameters of the body:
	// For more info: http://code.google.com/p/chipmunk-physics/wiki/cpBody
	ballBody->p = cpv(0, 0);
	// Add the body to the space so it will be simulated and move around.
	cpSpaceAddBody(space, ballBody);
	
	
	// Add a circle shape for the ball.
	// Shapes are always defined relative to the center of gravity of the body they are attached to.
	// When the body moves or rotates, the shape will move with it.
	// Additionally, all of the cpSpaceAdd*() functions return the thing they added so you can create and add in one go.
	cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	ballShape->e = 0.0f; ballShape->u = 0.9f;
  
  
  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  cpSpaceStep(space, 1.0f/60.0f);
}

