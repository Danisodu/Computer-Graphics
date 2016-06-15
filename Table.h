#pragma once
#include "StaticObject.h"
#include "Texture.h"

class Table :
	public StaticObject
{
private:
	Texture* _tex;
	bool _doItRightFlag = true;
public:
	Table();
	Table(double x, double y, double z);
	~Table();

	//void setTexture(Texture* t);
	void drawTopTable();
	void draw();
};