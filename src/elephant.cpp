#define _USE_MATH_DEFINES

#include <GL/gl.h>
#include <cmath>
#include "elephant.h"

Elephant::Elephant(float bw, float bh, float bl,
                   float hw, float hl,
                   float head_r, float pw, float pl) {
    body_width = bw;
    body_height = bh;
    body_length = bl;
    hoof_width = hw;
    hoof_length = hl;
    head_radius = head_r;
    prob_width = pw;
    prob_length = pl;

    mov[0] = mov[1] = mov[2] = 0;
    front_left[0] = front_left[1] = front_left[2] = 0;
    front_right[0] = front_right[1] = front_right[2] = 0;
    back_left[0] = back_left[1] = back_left[2] = 0;
    back_right[0] = back_right[1] = back_right[2] = 0;

    for (int i = 0; i < 8; i++)
        proboscis[i] = 10;
    for (int i = 8; i<15; i++)
        proboscis[i] = 0;
    for (int i = 15; i<20; i++)
        proboscis [i] = 20;

    body[0] = body[1] = 0;

    walk_fase = 1;

    quadric = gluNewQuadric();
}

Elephant::~Elephant() {
    gluDeleteQuadric(quadric);
}

bool Elephant::init(char * body_path) {
    if (!tex_body.loadTexture(body_path))
        return false;
    gluQuadricTexture(quadric, GL_TRUE);
    return true;
}

void Elephant::draw(float x, float y, float z) {

    glBindTexture(GL_TEXTURE_2D, tex_body.id);

    glPushMatrix();

    glTranslatef(x, y, z);
    glTranslatef(mov[0], mov[1], mov[2]);

    //Parte centrale del corpo
    glPushMatrix();
    glRotatef(body[1], 1, 0, 0);

    glPushMatrix();
    glScalef(body_width, body_height, body_length);

    glPushMatrix();
    glScalef(1, 1, 0.4);
    gluSphere(quadric, 0.5, 16, 16);
    glPopMatrix();

    gluCylinder(quadric, 0.5, 0.5, 1, 16, 16);

    glTranslatef(0, 0, 1);
    glScalef(1, 1, 0.4);
    gluSphere(quadric, 0.5, 16, 16);

    glPopMatrix();

    //Testa
    drawHead();


    //Zampa anteriore sinistra
    glPushMatrix();
    glTranslatef(3*body_width/8, 0, body_length);
    drawHoof(front_left);
    glPopMatrix();

    //Zampa anteriore destra
    glPushMatrix();
    glTranslatef(-3*body_width/8, 0, body_length);
    drawHoof(front_right);
    glPopMatrix();

    glPopMatrix();


    //Zampa posteriore sinistra
    glPushMatrix();
    glTranslatef(3*body_width/8, 0, 0);
    drawHoof(back_left);
    glPopMatrix();

    //Zampa posteriore destra
    glPushMatrix();
    glTranslatef(-3*body_width/8, 0, 0);
    drawHoof(back_right);
    glPopMatrix();


    glPopMatrix();
}

void Elephant::drawHoof(float rot[2]) {

    glPushMatrix();

    glRotatef(90+rot[0], 1, 0, 0);

    gluCylinder(quadric, hoof_width, hoof_width, 2*hoof_length/3, 16, 16);
    gluSphere(quadric, hoof_width, 16, 16);

    glTranslatef(0, 0, 2*hoof_length/3);
    glRotatef(rot[1], 1, 0, 0);
    gluCylinder(quadric, hoof_width, hoof_width, hoof_length/3, 16, 16);
    gluSphere(quadric, hoof_width, 16, 16);

    glPopMatrix();

}


void Elephant::drawHead() {

    glPushMatrix();

    glTranslatef(0, body_height/7, 1.2*body_length);


    //Testa
    gluSphere(quadric, head_radius, 16, 16);


    //Orecchie
    glPushMatrix();
    glTranslatef(head_radius, 0, 0);
    glScalef(head_radius, head_radius, 2);
    gluDisk(quadric, 0, 0.5, 16, 16);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-head_radius, 0, 0);
    glScalef(head_radius, head_radius, 2);
    gluDisk(quadric, 0, 0.5, 16, 16);
    glPopMatrix();

    //Proboscide
    glTranslatef(0, 0, head_radius/2);
    glRotatef(10, 1, 0, 0);
    for (int i=0; i<20; i++) {
            glTranslatef(0, 0, prob_length/20);
            glRotatef(proboscis[i], 1, 0, 0);
            gluSphere(quadric, prob_width-i*0.3, 16, 16);
            gluCylinder(quadric, prob_width-i*0.3, prob_width-(i+1)*0.3, prob_length/20, 16, 16);
    }

	glPopMatrix();

}

bool Elephant::walk(float length) {

    switch (walk_fase) {

    case 1:
            if (mov[2] < length)
                mov[2]+=1.8;
            front_right[0]-=3;
            front_right[1]+=3;
            back_left[0]-=3;
            back_left[1]+=3;

            front_left[0]+=1.8;
            back_right[0]+=1.8;

            if (front_left[0] >= 10)
                walk_fase = 2;
            break;

    case 2:
            if (mov[2] < length)
                mov[2]+=1.8;
            front_right[0]+=3;
            front_right[1]-=3;
            back_left[0]+=3;
            back_left[1]-=3;

            front_left[0]-=1.8;
            back_right[0]-=1.8;

            if (front_left[0] <= 0) {
                front_left[0] = front_left[1] =
                front_right[0] = front_right[1] =
                back_left[0] = back_left[1] =
                back_right[0] = back_right [1] =
                0;
                if (mov[2] >= length) return true;
                else walk_fase = 3;
            }
            break;

    case 3:
            if (mov[2] < length)
                mov[2]+=1.8;
            front_left[0]-=3;
            front_left[1]+=3;
            back_right[0]-=3;
            back_right[1]+=3;

            front_right[0]+=1.8;
            back_left[0]+=1.8;

            if (front_right[0] >= 10)
                walk_fase = 4;
            break;

    case 4:
            if (mov[2] < length)
                mov[2]+=1.8;
            front_left[0]+=3;
            front_left[1]-=3;
            back_right[0]+=3;
            back_right[1]-=3;

            front_right[0]-=1.8;
            back_left[0]-=1.8;

            if (front_right[0] <= 0) {
                front_left[0] = front_left[1] =
                front_right[0] = front_right[1] =
                back_left[0] = back_left[1] =
                back_right[0] = back_right [1] =
                0;
                if (mov[2] >= length) return true;
                else walk_fase = 1;
            }
            break;

    }

    return false;


}

bool Elephant::probToMouth() {

    if (proboscis[10] >= 20) return true;
    for (int i = 9; i < 20; i++) {
        proboscis[i] += 1;
    }
    return false;

}

bool Elephant::probNormal() {

    if (proboscis[10] <= 0) return true;
    for (int i = 9; i < 20; i++) {
        proboscis[i] -= 1;
    }
    return false;
}

bool Elephant::goDown() {

    if (body[1] >= 11) return true;
    body[1] += 0.3;
    front_right[0]-=1.8;
    front_right[1]+=1.5;
    front_left[0]-=1.8;
    front_left[1]+=1.5;

    probDrink();

    return false;
}

bool Elephant::goUp() {

    if (body[1] <= 0) return true;
    body[1] -= 0.3;
    front_right[0]+=1.8;
    front_right[1]-=1.5;
    front_left[0]+=1.8;
    front_left[1]-=1.5;

    probNotDrink();

    return false;
}

bool Elephant::probDrink() {

    if(proboscis[15] <= 0) return true;
    for (int i = 0; i < 8; i++)
        proboscis[i] -= 0.1;
    for (int i = 15; i<20; i++)
        proboscis [i] -= 0.4;
    return false;
}

bool Elephant::probNotDrink() {

    if(proboscis[15] >= 20) return true;
    for (int i = 0; i < 8; i++)
        proboscis[i] += 0.1;
    for (int i = 15; i<20; i++)
        proboscis [i] += 0.4;
    return false;
}
