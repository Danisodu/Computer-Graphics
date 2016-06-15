#include <iostream>
#include "Cheerio.h"
#include "Car.h"
#include <GL/glut.h>


Cheerio::Cheerio()
{
}


Cheerio::~Cheerio()
{
}

Cheerio::Cheerio(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

void Cheerio::setCurrentSpeed(double speed)
{
	_currentSpeed = speed;
}

double Cheerio::getCurrentSpeed()
{
	return _currentSpeed;
}

void Cheerio::setColided(bool boolean)
{
	_collided = boolean;
}

bool Cheerio::getColided()
{
	return _collided;
}

void Cheerio::setDirectionXY(double x, double y)
{
	_directionX = x;
	_directionY = y;
}

void Cheerio::draw() {

	glPushMatrix();

	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	GLfloat amb[] = { 1.0f,0.89f,0.0f,1.0f };
	GLfloat diff[] = { 0.41f,0.22f,0.0f,1.0f };
	GLfloat spec[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat shine = 76.8;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidTorus(0.1, 0.25, 8, 8);
	glColor3f(1, 0.5, 0);

	glPopMatrix();
}

void Cheerio::update(double delta_t)
{
	Vector3 speed(_directionX, _directionY, 0);
	if (_collided) {
		if (_currentSpeed > 0) {
			if (_currentSpeed - (delta_t)* FRICTION > 0) {
				_currentSpeed -= (delta_t)* FRICTION;
			}
			else {
				_currentSpeed = 0;
				_collided = false;
			}
		}
		else if (_currentSpeed < 0) {
			if (_currentSpeed + (delta_t)* FRICTION < 0) {
				_currentSpeed += (delta_t)* FRICTION;
			}
			else {
				_currentSpeed = 0;
				_collided = false;
			}
		}
		_speed = speed * _currentSpeed;
		_position = (_position + _speed);
	}
}
