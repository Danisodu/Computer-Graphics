#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

Plane::~Plane()
{
}

void Plane::setFileName(char* f) {
	_fileName = f;
}


/*
void Plane::setTexture(Texture* t) {
_tex = t;
}*/

void Plane::draw()
{
	if (_doItRightFlag) {
		_tex = new Texture(_fileName);
		_doItRightFlag = false;
	}
	_tex->bind();

	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());

	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-7.5, -7.5, 0); // bottom left

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-7.5, 7.5, 0); // top left

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(7.5, 7.5, 0); //top right

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(7.5, -7.5, 0); //bottom right

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}