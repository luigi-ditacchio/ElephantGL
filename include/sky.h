#ifndef _SKY_
#define _SKY_

#include <GL/glu.h>
#include "texture.h"

class Sky {

private:
	int R;
	int stack;
	int slices;

	GLUquadricObj * quadric;
	Texture texture;
	int disp_list;

public:
	Sky(int, int, int);
    ~Sky();
	bool init(char *);
	void draw();
};

#endif
