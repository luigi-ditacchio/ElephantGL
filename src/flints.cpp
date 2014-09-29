#include <GL/gl.h>
#include "flints.h"

Flints::Flints(float w, float l, float h, int nw, int nl) {
    width = w;
    length = l;
    height = h;
    num_width = nw;
    num_length = nl;

    disp_list = -1;
}


bool Flints::init(char * tex_path) {
    if (!texture.loadTexture(tex_path))
        return false;

    disp_list = glGenLists(1);
    glNewList(disp_list, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glBegin(GL_QUAD_STRIP);

    glTexCoord2f(0, num_length);             glVertex3f(-width/2, 0, length);
    glTexCoord2f(num_width, num_length);     glVertex3f(width/2, 0, length);
    glTexCoord2f(0, 0);                      glVertex3f(-width/2, 0, 0);
    glTexCoord2f(num_width, 0);              glVertex3f(width/2, 0, 0);

    glTexCoord2f(0, 0.5);             glVertex3f(-width/2, -height, 0);
    glTexCoord2f(num_width, 0.5);     glVertex3f(width/2, -height, 0);

    glEnd();

    glEndList();

    return true;

}

void Flints::draw(float x, float y, float z) {

    glPushMatrix();

    glTranslatef(x, y, z);

    glCallList(disp_list);

    glPopMatrix();
}
