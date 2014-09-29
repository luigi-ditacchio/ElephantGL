#ifndef _WATERFALL_
#define _WATERFALL_

#include "texture.h"

class Waterfall {

private:
	float width;
	float height;
	float mov;
	Texture texture;

public:
	Waterfall(float, float);
	bool init(char *);
	void draw(float, float, float);
	void move();

};

#endif
