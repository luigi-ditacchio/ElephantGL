#include <GL/gl.h>
#include <cmath>

#include "lake.h"


Lake::Lake(float wd, float ln, float wave1[3], float wave2[3]) {
    width = wd;
    length = ln;
    A1 = wave1[0];
    w1 = wave1[1];
    k1 = wave1[2];
    A2 = wave2[0];
    w2 = wave2[1];
    k2 = wave2[2];
    t = 0;
}

bool Lake::init(char * tex_path) {
    if (!texture.loadTexture(tex_path))
        return false;
    else
        return true;
}

void Lake::draw(float xp, float yp, float zp) {

    glPushMatrix();
    glTranslatef(xp, yp, zp);

    glBindTexture(GL_TEXTURE_2D, texture.id);


    float x = 0.0, z = 0.0;
    float incr = 20.0;
    while (z<length) {
        glBegin(GL_QUAD_STRIP);
        for (x=0; x<width; x+=incr) {

            glTexCoord2f(3*x/width, 3*z/length);	        glVertex3f(x, A2*sin(w2*t)*cos(k2*x) + A1*(1-z/length)*sin( w1*t + k1*z), z);
            glTexCoord2f(3*x/width, 3*(z+incr)/length);	    glVertex3f(x, A2*sin(w2*t)*cos(k2*x) + A1*(1-(z+incr)/length)*sin(w1*t + k1*(z+incr)), z+incr);
        }
        glEnd();
        z+=incr;
    }
    glPopMatrix();
}

void Lake::move() {
    t+=0.033;
}
