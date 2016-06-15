#include "Roadside.h"
#include <GL/glut.h>



Roadside::Roadside()
{
}

Roadside::~Roadside()
{
}

Roadside::Roadside(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

void Roadside::insertCheerio(Cheerio *c) {

	_cheerios.push_back(c);
}

void Roadside::draw() {

	for (auto cheerio : _cheerios) {
		(cheerio)->draw();
	}
}