#include "texture.h"

/* It makes use of IL library
 to load textures
 */
bool Texture::loadTexture(char * filename) {


	ILuint ImgId;
	ilGenImages(1, &ImgId);

	ilBindImage(ImgId);

	if (!filename)
		return false;

	if (!ilLoadImage((const ILstring)filename)) {
		return false;
	}

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);


	int bytesPerPixel = ilGetInteger(IL_IMAGE_BPP);
	if (bytesPerPixel != 3) {
		return false;
	}


	pixmap = new char[width * height * 3];
	if (!pixmap) {
		return false;
	}

	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, pixmap);


	ilBindImage(0);
	ilDeleteImage(ImgId);



	//OPENGL OPERATIONS
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D,
				       0,
				       GL_RGB,
				       width,
				       height,
				       0,
				       GL_RGB,
				       GL_UNSIGNED_BYTE,
				       pixmap);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	delete [] pixmap;

	return true;
}

Texture::Texture()
{
	width=0;
	height=0;
	pixmap=NULL;
	id=-1;
}

