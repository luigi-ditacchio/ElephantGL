#ifndef _LAKE_
#define _LAKE_

#include "texture.h"

class Lake {

private:
    float width;
    float length;
    float A1, w1, k1;
    float A2, w2, k2;
    float t;
    Texture texture;

public:
    Lake(float, float,
         float[3], float [3]);
    bool init(char *);
    void draw(float, float, float);
    void move();
};

#endif
