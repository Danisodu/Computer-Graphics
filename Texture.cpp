#include "Texture.h"


Texture::Texture(char* filename)
{
	int width, height;

	glGenTextures(1, &_texName);
	glBindTexture(GL_TEXTURE_2D, _texName);

	GLubyte *image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	if (image == NULL) { std::cout << "Error loading file\n"; }

	//give the image to openGl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	SOIL_free_image_data(image);
}

Texture::~Texture() 
{
}

void Texture::bind() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, _texName);
	glEnable(GL_TEXTURE_2D);
}


