#include "bomb.h"
#include <Math.h>

Bomb::Bomb(string sim_type) : Sprite("", 64, 64, BOMB_TAG) {
  srand(time(0));
  simulation_type = sim_type;
  elasticity = 0.8f;
  mass = 0.4f;
  exploding = false;
  destroyed = false;
  force = 13;
 // destroyed_phsics = false;
 // destroyed_sprite = false;
  
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
}

void Bomb::destroy(cpSpace *space) {
  if (!destroyed) {
    destroyed = true;
    if (simulation_type == "DYNAMIC")
      cpSpaceRemoveShape(space, bombShape);
    else
      cpSpaceRemoveStaticShape(space, bombShape);
    
    if (simulation_type == "DYNAMIC") cpSpaceRemoveBody(space, body);
    cpShapeFree(bombShape);
    cpBodyFree(body);
  
    for (int j=0; j < PARTICLE_TOTAL; j++) {
      delete particles[j];
      particles[j] = NULL;
    }
  
    delete [] particles;
  }
}

void Bomb::setElasticity(float _el) {
  elasticity = _el;
}

void Bomb::setMass(float _m) {
  mass = _m;
}

void Bomb::setForce(int _f) {
  force = _f;
}

int Bomb::getForce() {
  return force;
}

void Bomb::definePhysics(cpSpace *space) {
  // body
  if (simulation_type == "DYNAMIC")
    body = cpBodyNew(mass, cpMomentForCircle(mass, 0.0f, 15.0f, cpvzero));
  else
    body = cpBodyNew(INFINITY, INFINITY);
    
  body->p = cpv(x, y);
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);

  // ball shape
  bombShape = cpCircleShapeNew(body, 15.0f, cpvzero);
  bombShape->e = elasticity;
  bombShape->u = 0.2;
  bombShape->data = this;
  bombShape->collision_type = BOMB_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, bombShape);
  else
    cpSpaceAddStaticShape(space, bombShape);
}

void Bomb::display() {
  
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  GLfloat particle_vertices[] = {0,16,0, 16,16,0, 0,0,0, 16,0,0};
  
  if (!exploding) {
    glColor4f(alpha, alpha, alpha, alpha);
    
    float start_x = x;
    float start_y = y;

    float width = 48.0f;
    float height = 48.0f;

    float end_x = start_x + width;
    float end_y = start_y - height;

    float dx = end_x - start_x;
    float dy = end_y - start_y;

    GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
    
    TexManager::Instance()->bindTexture(9);
  
    glLoadIdentity();
    glTranslatef(start_x - width/2, start_y + height/2, 0.0);
    glTranslatef(width/2, -height/2, 0.0);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-width/2, height/2, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(3, GL_FLOAT, 0, tex);
  
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  } else {
    TexManager::Instance()->bindTexture(6);

    if (!destroyed) {
      for (int i=0; i < PARTICLE_TOTAL; i++) {
        if (!particles[i]->dead) {
          glLoadIdentity();
          glTranslatef(particles[i]->x - 16, particles[i]->y - 16, 0.0f);

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
  }
  
  TexManager::Instance()->unbindTexture();
}

void Bomb::explode(int timestep) {
  exploding = true; 
  cpVect blast_dir;
  
  for (int j=0; j < PARTICLE_TOTAL; j++) {
    if (particles[j]->dead) {
      blast_dir = cpvmult(cpvforangle(DEG2RAD(j*3)), (rand()%100)+40);
      particles[j]->x = x;
      particles[j]->y = y;
      particles[j]->x_speed = blast_dir.x;
      particles[j]->y_speed = blast_dir.y;
      particles[j]->ttl = 1250;
      particles[j]->birth = timestep;
      particles[j]->color = 100;
      particles[j]->dead = false;
    }
  }
  
}


void Bomb::manageParticles(int timestep, int timediff, cpSpace *space) {
  bool all_done = false;
  
  if (!destroyed) {
    for (int i=0; i < PARTICLE_TOTAL; i++) {
      if ((timestep - particles[i]->birth) >= particles[i]->ttl) {
        particles[i]->dead = true;
      }
    
      if (!particles[i]->dead) {
        particles[i]->x += (particles[i]->x_speed * (timediff * 0.01));
        particles[i]->y += (particles[i]->y_speed * (timediff * 0.01));
        all_done = false;
      } else {
        all_done = true;
      }
    }
  }
  
  // we are done managing all of the particles, so cut the physics and stop displaying the object
  if (all_done && exploding) {
    destroy(space);
  }
}
