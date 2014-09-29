#ifndef _FOREST_
#define _FOREST_

#include "tree.h"

class Forest {

private:
    Tree * tree;
    int num_width;
    int num_length;
    float tree_sep;
    int disp_list;

public:
    Forest(Tree *, int, int, float);
    bool init();
    void draw(float, float, float);
};

#endif
