#ifndef _ROCKS_
#define _ROCKS_

#include "texture.h"

class Rocks {

private:
	float height;
	float width;
	float length;

	Texture texture;
	int disp_list;

public:
	Rocks(float, float, float);
	bool init(char *);
	void draw(float, float, float);
};


#endif
