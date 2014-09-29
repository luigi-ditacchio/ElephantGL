
#include <GL/gl.h>

#include "waterfall.h"

Waterfall::Waterfall(float h, float w) {
	height = h;
	width = w;
	mov = 0;
}

bool Waterfall::init(char * tex_path) {
	if (!texture.loadTexture(tex_path))
		return false;
	else
		return true;
}

void Waterfall::draw(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glBindTexture(GL_TEXTURE_2D, texture.id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glBegin(GL_QUADS);

	glTexCoord2f(0, mov);	    glVertex3f(-width/2, height/2, 0);
	glTexCoord2f(1, mov);	    glVertex3f(width/2, height/2, 0);
	glTexCoord2f(1, mov-8);		glVertex3f(width/2, -height/2, 0);
	glTexCoord2f(0, mov-8);		glVertex3f(-width/2, -height/2, 0);

	glEnd();


	glPopMatrix();
}


void Waterfall::move() {
	mov += 0.3;
}


