#pragma once
#include "StaticObject.h"
#include <GL\glut.h>
#include <gl\gl.h>
#include <gl\glu.h> 
#include <gl\glut.h>

class Vela :
	public StaticObject
{
public:
	Vela(){}
	~Vela(){}

	void draw();
};