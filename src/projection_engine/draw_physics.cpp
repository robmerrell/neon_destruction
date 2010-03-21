#include "draw_physics.h"

/**
 * basic algorithm found at: http://basic4gl.wikispaces.com/2D+Drawing+in+OpenGL
 */
static void drawCircleShape(cpBody *body, cpCircleShape *circle) {
  cpVect center = circle->tc;
  
  glLoadIdentity();
  glTranslatef(center.x, center.y, 0.0);
  glBegin(GL_LINE_STRIP);
    glColor4f(BODY_COLOR);
    glVertex2f(center.x, center.y);
    for (int i = 0; i < 360; i++) {
      glVertex2f(center.x + sin(i) * circle->r, center.y + cos(i) * circle->r);
    }
  glEnd();
}

// static void
// drawPolyShape(cpBody *body, cpPolyShape *poly)
// {
//  int count = count=poly->numVerts;
//  glVertexPointer(2, GL_DOUBLE, 0, poly->tVerts);
//  
//  if(!poly->shape.sensor){
//    glColor_from_pointer(poly);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, count);
//  }
//  
//  glColor3f(LINE_COLOR);
//  glDrawArrays(GL_LINE_LOOP, 0, count);
// }

static void drawPolyShape(cpBody *body, cpPolyShape *poly) {
  int count = poly->numVerts;

  glLoadIdentity();
  glBegin(GL_LINE_STRIP);
    glColor4f(BODY_COLOR);
    for (int i = 0; i < count; i++) {
      cpVect poly_vert = poly->verts[i];
      glVertex2f(poly_vert.x, poly_vert.y);
    }
    
    glVertex2f(poly->verts[0].x, poly->verts[0].y);
  glEnd();

}

static void drawObject(void *ptr, void *unused) {
	cpShape *shape = (cpShape *)ptr;
	cpBody *body = shape->body;
	
	switch(shape->klass->type){
		case CP_CIRCLE_SHAPE:
			drawCircleShape(body, (cpCircleShape *)shape);
			break;
    // case CP_SEGMENT_SHAPE:
    //  drawSegmentShape(body, (cpSegmentShape *)shape);
    //  break;
    case CP_POLY_SHAPE:
     drawPolyShape(body, (cpPolyShape *)shape);
     break;
    // default:
    //  printf("Bad enumeration in drawObject().\n");
	}
}

void drawPhysics(cpSpace* space) {
  cpSpaceHashEach(space->activeShapes, &drawObject, NULL);
	cpSpaceHashEach(space->staticShapes, &drawObject, NULL);
}