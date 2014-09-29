#ifndef _GRASS_
#define _GRASS_

#include "texture.h"


class Grass {

private:
    float width;
    float length;
    Texture texture;
    int disp_list;

public:
    Grass(float, float);
    bool init(char *);
    void draw(float, float, float);

};

#endif
