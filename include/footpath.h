#ifndef _FOOTPATH_
#define _FOOTPATH_

#include "texture.h"

class FootPath {

private:
    float length;
    float width;
    Texture texture;
    int disp_list;

public:
    FootPath(float, float);
    bool init(char *);
    void draw(float, float, float);
};

#endif
