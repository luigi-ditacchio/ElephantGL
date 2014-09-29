#include <GL/gl.h>
#include "forest.h"

Forest::Forest(Tree * t, int nw, int nl, float ts) {
    tree = t;
    num_width = nw;
    num_length = nl;
    tree_sep = ts;
    disp_list = -1;
}

bool Forest::init() {

    disp_list = glGenLists(1);
    glNewList(disp_list, GL_COMPILE);

    for (int i = 0; i<num_width; i++) {
        for (int j = 0; j<num_length; j++) {

            tree->draw( (tree->getWidth()+tree_sep)*i, 0, (tree->getWidth()+tree_sep)*j);
        }
    }
    glEndList();

    return true;
}

void Forest::draw(float x, float y, float z) {

    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(disp_list);
    glPopMatrix();

}
