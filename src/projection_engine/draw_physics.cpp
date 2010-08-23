#include "draw_physics.h"

void draw_chipmunk(cpSpace *space) {
  cpSpaceHashEach(space->activeShapes, &draw_shapes, NULL);
	cpSpaceHashEach(space->staticShapes, &draw_shapes, NULL);
	
	cpArray *constraints = space->constraints;

  glColor4f(0.5f, 1.0f, 0.5f, 1.0f);
  for(int i=0, count = constraints->num; i<count; i++){
    draw_constraint((cpConstraint *)constraints->arr[i]);
  }
}

static void draw_shapes(void *ptr, void *unused) {
	cpShape *shape = (cpShape *)ptr;
	cpBody *body = shape->body;
	
	switch(shape->klass->type) {
	  case CP_CIRCLE_SHAPE:
      draw_circle(body, (cpCircleShape *)shape);
      break;
    case CP_SEGMENT_SHAPE:
      draw_segment(body, (cpSegmentShape *)shape);
      break;
    case CP_POLY_SHAPE:
			draw_poly(body, (cpPolyShape *)shape);
			break;
	}
}

static void draw_circle(cpBody *body, cpCircleShape *circle) {
  GLfloat vertices[24];
  
  glLoadIdentity();
  glTranslatef(circle->tc.x, circle->tc.y, 0);
  
  int x = 0;
  for (int i = 0; i < 360; i += 30) {
    vertices[x] = (cos(DEGREES_TO_RADIANS(i)) * 1) * circle->r;
    x++;
    vertices[x] = (sin(DEGREES_TO_RADIANS(i)) * 1) * circle->r;
    x++;
  }
    
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  glDrawArrays(GL_LINE_LOOP, 0, 12);
  
  glDisableClientState(GL_VERTEX_ARRAY);
}

static void draw_segment(cpBody *body, cpSegmentShape *seg) {
  cpVect a = seg->ta;
	cpVect b = seg->tb;

  glLoadIdentity();
  glTranslatef(0, 0, 0);
  
  GLfloat vertices[] = {a.x, a.y, b.x, b.y};
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glDrawArrays(GL_LINE_LOOP, 0, 2);

  glDisableClientState(GL_VERTEX_ARRAY);
}

static void draw_poly(cpBody *body, cpPolyShape *poly)
{
	int count = poly->numVerts;
  int v_count = 0;
  GLfloat vertices[count * 2];
	
  float width = (poly->tVerts[2].x - poly->tVerts[0].x) / 2.0f;
  float height = (poly->tVerts[2].y - poly->tVerts[0].y) / 2.0f;
	
	glLoadIdentity();
  glTranslatef(poly->tVerts[0].x + width, poly->tVerts[0].y + height, 0);

  for (int i = 0; i < count; i++) {
    vertices[v_count] = poly->verts[i].x;
    v_count++;
    
    vertices[v_count] = poly->verts[i].y;
    v_count++;
  }

	glVertexPointer(2, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);	
	glDrawArrays(GL_LINE_LOOP, 0, count);
	glDisableClientState(GL_VERTEX_ARRAY);
}

static void draw_constraint(cpConstraint *constraint) {
  cpBody *body_a = constraint->a;
  cpBody *body_b = constraint->b;

  const cpConstraintClass *klass = constraint->klass;
  if(klass == cpPinJointGetClass()) {
    cpPinJoint *joint = (cpPinJoint *)constraint;

    cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchr1, body_a->rot));
    cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchr2, body_b->rot));
    
    glLoadIdentity();
    glTranslatef(0, 0, 0);

    GLfloat vertices[] = {a.x, a.y, b.x, b.y};
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
  }
}