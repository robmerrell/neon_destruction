#include "box.h"

Box::Box(string sim_type) : Sprite("", 64, 64, BOX_TAG) {
  simulation_type = sim_type;

  x = 0.0f;
  y = 0.0f;
  width = 0.0f;
  height = 0.0f;  
  mass = 10.0f;
}

void Box::destroy(cpSpace *space) {
  if (simulation_type == "DYNAMIC")
    cpSpaceRemoveShape(space, boxShape);
  else
    cpSpaceRemoveStaticShape(space, boxShape);
    
  cpSpaceRemoveBody(space, body);
  cpShapeFree(boxShape);
  cpBodyFree(body);
}

void Box::setWidth(float _width) {
  width = _width;
}

void Box::setHeight(float _height) {
  height = _height;
}

void Box::setMass(float _m) {
  mass = _m;
}

void Box::definePhysics(cpSpace *space) {
  // body
  cpVect verts[] = { cpv(-width/2 + 3, -height/2 + 9), cpv(-width/2 + 3, height/2 - 9), cpv(width/2 - 3, height/2 - 9), cpv(width/2 - 3, -height/2 + 9) };
  if (simulation_type == "DYNAMIC")
    body = cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero));
  else
    body = cpBodyNew(INFINITY, INFINITY);
  body->p = cpv(x, y);
  cpBodySetAngle(body, DEG2RAD(angle));
  if (simulation_type == "DYNAMIC") cpSpaceAddBody(space, body);
  
  // poly shape box
  boxShape = cpPolyShapeNew(body, 4, verts, cpvzero);
  boxShape->e = 0.1;
  boxShape->u = 0.15;
  boxShape->data = this;
  boxShape->collision_type = BOX_COLLISION;
  
  if (simulation_type == "DYNAMIC")
    cpSpaceAddShape(space, boxShape);
  else
    cpSpaceAddStaticShape(space, boxShape);
}

void Box::display() {
  float start_x = x;
  float start_y = y;
  
  float end_x = start_x + width;
  float end_y = start_y - height;
  
  float dx = end_x - start_x;
  float dy = end_y - start_y;
  
  int hti = 0; // texture index
  int vti = 0;
  
  // get the points in the texture map
  for (int i = 0; i < sizeof(PLATFORM_SIZES)/sizeof(int); i++) {
    if (PLATFORM_SIZES[i] == width)
      hti = i;
      
    if (PLATFORM_SIZES[i] == height)
      vti = i;
  }
  
  GLfloat vertices_hor[] = {0,-25.0f,0, dx,-25.0f,0, 0,0,0, dx,0,0};
  GLfloat tex_hor[] = {0,PLATFORM_BOTTOM[hti],0, PLATFORM_RIGHT[hti],PLATFORM_BOTTOM[hti],0, 0,PLATFORM_TOP[hti],0, PLATFORM_RIGHT[hti],PLATFORM_TOP[hti],0};
  
  GLfloat vertices_vert[] = {0,-25.0f,0, dy,-25.0f,0, 0,0,0, dy,0,0};
  GLfloat tex_vert[] = {0,PLATFORM_BOTTOM[vti],0, PLATFORM_RIGHT[vti],PLATFORM_BOTTOM[vti],0, 0,PLATFORM_TOP[vti],0, PLATFORM_RIGHT[vti],PLATFORM_TOP[vti],0};
  
  glColor4f(alpha, alpha, alpha, alpha);
  
  if (simulation_type == "DYNAMIC")
    TexManager::Instance()->bindTexture(8);
  else
    TexManager::Instance()->bindTexture(7);
    
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  // bottom
  glLoadIdentity();
  glTranslatef(start_x - width/2, start_y + height/2, 0.0);
  glTranslatef(width/2, -height/2, 0.0);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-width/2, height/2, 0.0);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices_hor);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_hor);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // right
  glTranslatef(width, -height, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_vert);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_vert);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // top
  glTranslatef(0.0f, 0.0f, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_hor);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_hor);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // left
  glTranslatef(width, -height, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_vert);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_vert);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  
  // bottom
  /*
  glLoadIdentity();
  glTranslatef(start_x - width/2, start_y + height/2, 0.0);
  glTranslatef(width/2, -height/2, 0.0);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-width/2, height/2, 0.0);
  
  glVertexPointer(3, GL_FLOAT, 0, vertices_hor);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_hor);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // right
  glTranslatef(width + 5.5f, -height + 1.0f, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_vert);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_vert);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // top
  glTranslatef(-1.0f, -5.5f, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_hor);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_hor);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
  // left
  glTranslatef(width + 5.5f, -height + 1.0f, 0.0f);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, vertices_vert);
  glTexCoordPointer(3, GL_FLOAT, 0, tex_vert);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  */
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
  TexManager::Instance()->unbindTexture();
}