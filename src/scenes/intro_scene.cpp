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
	cpBody *ballBody = cpBodyNew(mass, INFINITY);
	// Set some parameters of the body:
	// For more info: http://code.google.com/p/chipmunk-physics/wiki/cpBody
	ballBody->p = cpv(100, 0);
	// Add the body to the space so it will be simulated and move around.
	cpSpaceAddBody(space, ballBody);
	
	
	// Add a circle shape for the ball.
	// Shapes are always defined relative to the center of gravity of the body they are attached to.
	// When the body moves or rotates, the shape will move with it.
	// Additionally, all of the cpSpaceAdd*() functions return the thing they added so you can create and add in one go.
	cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	ballShape->e = 0.5f; ballShape->u = 0.9f;
  
  cpBody *staticBody = cpBodyNew(INFINITY, INFINITY);
    // Create A ground segment along the bottom of the screen
	cpShape *ground = cpSegmentShapeNew(staticBody, cpv(0, 300), cpv(640, 300), 1.0f);
	// Set some parameters of the shape.
	// For more info: http://code.google.com/p/chipmunk-physics/wiki/cpShape
	ground->e = 1.0f; ground->u = 1.0f;
	// Add the shape to the space as a static shape
	// If a shape never changes position, add it as static so Chipmunk knows it only needs to
	// calculate collision information for it once when it is added.
	// Do not change the postion of a static shape after adding it.
	cpSpaceAddStaticShape(space, ground);
  
  
  // start the game loop
  scheduleLoop(60);
}


void IntroScene::gameLoop() {
  cpSpaceStep(space, 1.0f/60.0f);
}

