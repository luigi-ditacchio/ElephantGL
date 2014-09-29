#include <GL/gl.h>
#include <cmath>

#include "sky.h"

#define _USE_MATH_DEFINES
#define PI    ((float)M_PI)

Sky::Sky(int r, int st, int sl) {
	R = r;
	stack = st;
	slices = sl;
	quadric = gluNewQuadric();
	disp_list = -1;
}

Sky::~Sky() {
    gluDeleteQuadric(quadric);
}

bool Sky::init(char * tex_path) {

	if (!texture.loadTexture(tex_path)) {
		return false;
	}

	disp_list = glGenLists(1);
	glNewList(disp_list, GL_COMPILE);

    gluQuadricTexture(quadric, GL_TRUE);

    glBindTexture(GL_TEXTURE_2D, texture.id);
/*
	float alfa, beta;

	for (beta = 0; beta <= PI/2; beta += (PI/2)/stack) {
		glBegin(GL_QUAD_STRIP);
		for (alfa=0; alfa <= 2*PI; alfa += 2*PI/slices) {

			glTexCoord2f(alfa/(2*PI), (PI/2 - beta)/(PI/2));		glVertex3f( R*cos(beta)*cos(alfa), R*sin(beta), R*cos(beta)*sin(alfa));
			glTexCoord2f(alfa/(2*PI), (PI/2 - (beta + (PI/2)/stack))/(PI/2));		glVertex3f( R*cos(beta + (PI/2)/stack)*cos(alfa), R*sin(beta+(PI/2)/stack), R*cos(beta+(PI/2)/stack)*sin(alfa));
		}
		glTexCoord2f(1, (PI/2 - beta)/(PI/2));        glVertex3f( R*cos(beta)*cos(2*PI), R*sin(beta), R*cos(beta)*sin(2*PI));
		glTexCoord2f(1, (PI/2 - (beta + (PI/2)/stack))/(PI/2));       glVertex3f( R*cos(beta + (PI/2)/stack)*cos(2*PI), R*sin(beta + (PI/2)/stack), R*cos(beta + (PI/2)/stack)*sin(2*PI));

		glEnd();
	}
*/
    glRotatef(90, 1, 0, 0);
    gluSphere(quadric, R, stack, slices);
	glEndList();

	return true;

 }

void Sky::draw() {
    glPushMatrix();
	glCallList(disp_list);
	glPopMatrix();
}
