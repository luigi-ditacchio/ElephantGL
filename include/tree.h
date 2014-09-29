#ifndef _TREE_
#define _TREE_

#include <GL/glu.h>
#include "texture.h"

class Tree {

private:
    float trunk_radius;
    float trunk_length;
    float leaves_radius;
    float rot;
    GLUquadricObj * quadric;
    Texture trunk_tex;
    Texture leaves_tex;
    int disp_list;

public:
    Tree(float, float, float);
    ~Tree();
    bool init(char *, char *);
    void draw(float, float, float);
    void move();
    float getWidth();
};

#endif
