#include <GL/gl.h>

#include "rocks.h"

Rocks::Rocks(float h, float w, float l) {
	height = h;
	width = w;
	length = l;
	disp_list = -1;
}

bool Rocks::init(char * tex_path) {
	if (!texture.loadTexture(tex_path))
		return false;

	disp_list = glGenLists(1);
	glNewList(disp_list, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, texture.id);


	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);     glVertex3f(-width/2, height, 0);
	glTexCoord2f(0, 0);     glVertex3f(-width/2, 0, 0);

	glTexCoord2f(1, 0);     glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);     glVertex3f(0, height, 0);

	glEnd();


	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);     glVertex3f(-(width/2+length), height, length);
	glTexCoord2f(0, 0);     glVertex3f(-(width/2+length), 0, length);

	glTexCoord2f(1, 0);     glVertex3f(-width/2, 0, 0);
	glTexCoord2f(1, 1);     glVertex3f(-width/2, height, 0);

    glEnd();


    glBegin(GL_QUADS);

	glTexCoord2f(0, 1);     glVertex3f(-(width/2+2*length), height, length);
	glTexCoord2f(0, 0);     glVertex3f(-(width/2+2*length), 0, length);

	glTexCoord2f(1, 0);     glVertex3f(-(width/2+length), 0, length);
	glTexCoord2f(1, 1);     glVertex3f(-(width/2+length), height, length);

    glEnd();


	glEndList();

	return true;

}

void Rocks::draw(float x, float y, float z) {
	glPushMatrix();

	glTranslatef(x, y, z);

	glCallList(disp_list);

	glPushMatrix();
	glScalef(-1, 1, 1);
	glCallList(disp_list);
	glPopMatrix();

	glPopMatrix();
}
