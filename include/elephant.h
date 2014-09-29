#ifndef _ELEPHANT_
#define _ELEPHANT_

#include <GL/glu.h>
#include "texture.h"


class Elephant {

private:
    float body_width, body_height, body_length;
    float hoof_width, hoof_length;
    float head_radius, prob_width, prob_length;

    float mov[3];
    float front_left[3], front_right[3], back_left[3], back_right[3];
    float proboscis[20];
    float body[2];

    int walk_fase;

    Texture tex_body;
    GLUquadricObj * quadric;

    void drawHoof(float []);
    void drawHead();

public:
    Elephant(float, float, float,
             float, float,
             float, float, float);
    ~Elephant();
    bool init(char *);
    void draw(float, float, float);

    bool walk(float);
    bool probToMouth();
    bool probNormal();
    bool goDown();
    bool goUp();
    bool probDrink();
    bool probNotDrink();
};

#endif
