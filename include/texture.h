#ifndef _TEXTURE_
#define _TEXTURE_

#include "GL/gl.h"
#include "IL/il.h"


class Texture {

public:
	GLuint id;
	char *pixmap;
	int width;
	int height;

	Texture();

	bool loadTexture(char *filename);

};



#endif
