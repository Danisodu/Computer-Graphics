#pragma once
#include "StaticObject.h"
#include "Cheerio.h"
#include <list>


class Roadside :
	public StaticObject
{
protected:
	std::list<Cheerio*> _cheerios;

public:
	Roadside();
	Roadside(double x, double y, double z);
	~Roadside();
	void insertCheerio(Cheerio *c);
	void draw();
};