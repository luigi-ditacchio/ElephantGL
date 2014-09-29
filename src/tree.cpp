#include <GL/gl.h>
#include "tree.h"

Tree::Tree(float tr, float tl, float lr) {
    trunk_radius = tr;
    trunk_length = tl;
    leaves_radius = lr;
    rot = 0;
    quadric = gluNewQuadric();
    disp_list = -1;
}


Tree::~Tree() {
    gluDeleteQuadric(quadric);
}


bool Tree::init(char * tex_path_t, char * tex_path_l) {
    if (!trunk_tex.loadTexture(tex_path_t) || !leaves_tex.loadTexture(tex_path_l))
        return false;

    gluQuadricTexture(quadric, GL_TRUE);

    disp_list = glGenLists(1);
    glNewList(disp_list, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, trunk_tex.id);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quadric, trunk_radius, trunk_radius, trunk_length, 16, 1);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, leaves_tex.id);
    glTranslatef(0, trunk_length + 3*leaves_radius/4, 0);
    glRotatef(180, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    gluSphere(quadric, leaves_radius, 16, 16);

    glEndList();

    return true;
}


void Tree::draw(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rot, 0, 0, 1);
    glCallList(disp_list);
    glPopMatrix();
}


void Tree::move() {
    rot += 0.1;
}

float Tree::getWidth() {
    return leaves_radius*2;
}
