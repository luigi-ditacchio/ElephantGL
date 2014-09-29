#ifndef _FLINTS_
#define _FLINTS_

#include "texture.h"

class Flints {

private:
    float width;
    float length;
    float height;
    int num_width;
    int num_length;

    Texture texture;
    int disp_list;

public:
    Flints(float, float, float, int, int);
    bool init(char *);
    void draw(float, float, float);
};

#endif
