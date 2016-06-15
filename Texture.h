#pragma once
#include <iostream>
#include "SOIL.h"
#include <GL/glut.h>
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h>


class Texture
{
	private:
		GLuint _texName;
	public:
		Texture(char* filename);
		~Texture();
		void bind();
};