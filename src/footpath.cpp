#include <GL/gl.h>
#include "footpath.h"

FootPath::FootPath(float l, float w) {
    length = l;
    width = w;
    disp_list = -1;
}

bool FootPath::init(char * tex_path) {
    if(!texture.loadTexture(tex_path))
        return false;

    disp_list = glGenLists(1);
    glNewList(disp_list, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);     glVertex3f(-width/2, 0, -length/2);
    glTexCoord2f(1, 0);     glVertex3f(width/2, 0, -length/2);
    glTexCoord2f(1, 20);     glVertex3f(width/2, 0, length/2);
    glTexCoord2f(0, 20);     glVertex3f(-width/2, 0, length/2);
    glEnd();

    glEndList();

    return true;
}

void FootPath::draw(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(disp_list);
    glPopMatrix();
}
