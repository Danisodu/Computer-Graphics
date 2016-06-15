#pragma once
#include "StaticObject.h"
#include "Texture.h"

class Plane :
	public StaticObject
{
private:
	//Texture* _tex;
	char* _fileName;
	Texture* _tex;
	bool _doItRightFlag = true;
public:
	Plane();
	Plane(double x, double y, double z);
	void setFileName(char* f);
	~Plane();

	//void setTexture(Texture* t);
	void draw();
};