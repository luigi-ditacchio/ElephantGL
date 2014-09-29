#include "grass.h"

Grass::Grass(float w, float l) {
    width = w;
    length = l;
    disp_list = -1;
}

bool Grass::init(char * tex_path) {
    if(!texture.loadTexture(tex_path))
        return false;
    disp_list = glGenLists(1);
    glNewList(disp_list, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);     glVertex3f(-width/2, 0, -length/2);
    glTexCoord2f(20, 0);     glVertex3f(width/2, 0, -length/2);
    glTexCoord2f(20, 40);     glVertex3f(width/2, 0, length/2);
    glTexCoord2f(0, 40);     glVertex3f(-width/2, 0, length/2);

    glEnd();

    glEndList();

    return true;
}

void Grass::draw(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(disp_list);
    glPopMatrix();
}
