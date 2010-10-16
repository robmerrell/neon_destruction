#include "ball.h"
#include <iostream>
#include <Math.h>

using namespace std;

Ball::Ball(float x, float y) : Sprite("", 64, 64, BALL_TAG) {
  srand(time(0));
  setX(x);
  setY(y);
  
  last_particle_x = x;
  last_particle_y = y;
  
  particles = new Particle *[PARTICLE_TOTAL];
  
  for (int j=0; j < PARTICLE_TOTAL; j++) {
    Particle* p = new Particle;
    p->color = 0;
    p->x = 0;
    p->y = 0;
    p->x_speed = 0;
    p->y_speed = 0;
    p->birth = 0;
    p->ttl = 0;
    p->dead = true;
    particles[j] = p;
  }
  
  alpha = 1.0f;
  animation_state = ANIMATE_NONE;
}

Ball::~Ball() {
}

void Ball::destroy(cpSpace *space) {
  cpSpaceRemoveShape(space, ballShape);
  cpSpaceRemoveBody(space, body);
  cpShapeFree(ballShape);
  cpBodyFree(body);
  
  for (int j=0; j < PARTICLE_TOTAL; j++) {
    delete particles[j];
    particles[j] = NULL;
  }
  
  delete [] particles;
}

void Ball::definePhysics(cpSpace *space) {
  // body
  body = cpBodyNew(1.0f, INFINITY);
  body->p = cpv(x, y);
  cpSpaceAddBody(space, body);

  // ball shape
  ballShape = cpCircleShapeNew(body, 10.0, cpvzero);
  ballShape->e = 0.8;
  ballShape->u = 0.2;
  ballShape->data = this;
  ballShape->collision_type = BALL_COLLISION;
  cpSpaceAddShape(space, ballShape);
}

void Ball::applyImpulse(cpVect mouse, cpVect originating, float g) {
  float x, y;
  
  if (g < 0) {
    x = originating.x - mouse.x;
    y = originating.y - mouse.y;    
  } else {
    x = mouse.x - originating.x;
    y = originating.y - mouse.y;
  }
  
  float angle1, angle2;
  float diff = sqrt(x*x  + y*y);
  float vel = 200 + diff;

  float tmp = sqrt(pow(vel,4) - g * (g * pow(x, 2) + 2 * y * pow(vel,2)));
  
  angle2 = atan2(pow(vel,2) - tmp, g*x);
  
  float d2 = RAD2DEG(angle2);
  float d3;
  
  if (g > 0)
    d3 = 360 - d2;
  else
    d3 = d2;
  
  cpVect f = cpvmult(cpvforangle(DEG2RAD(d3)), vel);
  cpBodyApplyImpulse(body, cpv(f.x, f.y), cpvzero);
}

void Ball::display() {
  GLfloat ball_vertices[] = {0,64,1, 64,64,1, 0,0,1, 64,0,1};
  GLfloat particle_vertices[] = {0,16,0, 16,16,0, 0,0,0, 16,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  TexManager::Instance()->bindTexture(1);
  
  glLoadIdentity();
  glTranslatef(body->p.x - 32, body->p.y - 32, 0.0f);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3, GL_FLOAT, 0, ball_vertices);
  glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
  glColor4f(alpha, alpha, alpha, alpha);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
  
  TexManager::Instance()->bindTexture(6);
  
  for (int i=0; i < PARTICLE_TOTAL; i++) {
    if (!particles[i]->dead) {
      glLoadIdentity();
      glTranslatef(particles[i]->x - 16, particles[i]->y - 16, 0.0f);
      
      glColor4f(colors[particles[i]->color][0], colors[particles[i]->color][1], colors[particles[i]->color][2], 1.0f);
  
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
      glVertexPointer(3, GL_FLOAT, 0, particle_vertices);
      glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  }
  
}

void Ball::emitParticles(int timestep) {
  float dx = x - last_particle_x;
  float dy = y - last_particle_y;
  float distance = sqrt(dx * dx + dy * dy);
  
  if (distance <= 20) return;
  
  last_particle_x = x;
  last_particle_y = y;
  
  // emit 3 particles at a time
  for (int i=0; i < 3; i++) {
    for (int j=0; j < PARTICLE_TOTAL; j++) {
      if (particles[j]->dead) {
        particles[j]->x = x + 5.0f + i;
        particles[j]->y = y + 5.0f + i;
        particles[j]->x_speed = float((rand() % 10)-6.0f);
        particles[j]->y_speed = float((rand() % 30)-5.0f);
        particles[j]->ttl = rand()%(1250-750)+750;
        particles[j]->birth = timestep;
        particles[j]->color = (rand() % 12);
        particles[j]->dead = false;
        break;
      }
    }
  }
}

void Ball::manageParticles(int timestep, int timediff) {
  for (int i=0; i < PARTICLE_TOTAL; i++) {
    if ((timestep - particles[i]->birth) >= particles[i]->ttl) {
      particles[i]->dead = true;
    }
    
    if (!particles[i]->dead) {
      particles[i]->x += (particles[i]->x_speed * (timediff * 0.01));
      particles[i]->y += (particles[i]->y_speed * (timediff * 0.01));
    }
  }
}
