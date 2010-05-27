#include "box.h"

Box::Box(int type, int sim_type) : Sprite("", 64, 64, BOX_TAG) {
  box_type = type;
  simulation_type = sim_type;

  x = 0.0f;
  y = 0.0f;
  
  // based on the box type determine width and height
  switch (type) {
    case BOX_TALL_SKINNY:
      width = 20.0f;
      height = 150.0f;
      break;
      
    case BOX_TALL_MEDIUM:
      width = 60.0f;
      height = 150.0f;
      break;
      
    case BOX_TALL_WIDE:
      width = 100.0f;
      height = 150.0f;
      break;
      
    case BOX_SMALL_SQUARE:
      width = 25.0f;
      height = 25.0f;
      break;

    case BOX_MEDIUM_SQUARE:
      width = 60.0f;
      height = 60.0f;
      break;

    case BOX_LARGE_SQUARE:
      width = 120.0f;
      height = 120.0f;
      break;
    
    default:
      width = 100.0f;
      height = 100.0f;
  }
}

void Box::definePhysics(cpSpace *space) {
  // body
  cpVect verts[] = { cpv(-width/2, -height/2), cpv(-width/2, height/2), cpv(width/2, height/2), cpv(width/2, -height/2) };
  body = cpBodyNew(10.0f, cpMomentForPoly(10.0f, 4, verts, cpvzero));
  body->p = cpv(x, y);
  cpBodySetAngle(body, angle);
  cpSpaceAddBody(space, body);
  
  // poly shape box
  cpShape *boxShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  boxShape->e = 0.1;
  boxShape->u = 0.3;
  boxShape->data = this;
  boxShape->collision_type = BOX_COLLISION;
  
  cpSpaceAddShape(space, boxShape);
}

void Box::display() {
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  GLfloat vertices[] = {0,dy,0, dx,dy,0, 0,0,0, dx,0,0};
  GLfloat tex[] = {0,1,0, 1,1,0, 0,0,0, 1,0,0};
  
  
  TexManager::Instance()->bindTexture(8);
  
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
  
  TexManager::Instance()->unbindTexture();
}