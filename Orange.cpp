#include "Orange.h"
#include "stdlib.h"
#include <GL/glut.h>


Orange::Orange()
{
}

Orange::Orange(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

Orange::~Orange()
{
}

void Orange::setId(int i) {
	_id = i;
}

void Orange::setDirection(double x, double y, double z) {
	_direction.setXYZ(x, y, z);
}

void Orange::setAngle(double a) {
	_angle = a;
}

void Orange::setLifeState(bool b) {
	_alive = b;
}

void Orange::setSpeedState(bool b) {
	_raiseSpeed = b;
}

void Orange::setCurrentSpeed(double s) {
	_currentSpeed = s;
}

void Orange::setWaitingState(bool b) {
	_waitingToLive = b;
}

int Orange::getId() {
	return _id;
}

double Orange::getCurrentSpeed() {
	return _currentSpeed;
}

bool Orange::getSpeedState() {
	return _raiseSpeed;
}

bool Orange::getWaitingState() {
	return _waitingToLive;
}

double Orange::generateNumber(double max, double min) {
	double n = (max - (min)) * ((double)rand() / (double)RAND_MAX) + (min);
	return n;
}

double Orange::generatePosition(int quadrante, int axis) {

	switch (quadrante) {
	case 0:
		if (axis == 0) { return -ORANGEINIPOSITION; } //axis=0 para o X, axis=1 para o Y

		else { return generateNumber(15, -15); }

	case 1:
		if (axis == 0) { return generateNumber(15, -15); }

		else { return ORANGEINIPOSITION; }

	case 2:
		if (axis == 0) { return ORANGEINIPOSITION; }

		else {
			return generateNumber(15, -15);
		}

	case 3:
		if (axis == 0) { return generateNumber(15, -15); }

		else { return -ORANGEINIPOSITION; }

	default:
		std::cout << "Random Error\n";
		return -1;
	}
}

void Orange::update(double s)
{

	Vector3 copyDirection = _direction;
	Vector3 copyPosition = _position;
	Vector3 updatedPosition;

	_speed = copyDirection * _currentSpeed;
	updatedPosition = copyPosition + _speed;
	_position = updatedPosition;
	_angle += ANGLEINCREASE;
}

void Orange::draw()
{
	if (_alive == true) {
		
		glPushMatrix();
		glTranslatef(_position.getX(), _position.getY(), _position.getZ());
		glRotatef(_angle, -_direction.getY(), _direction.getX(), _direction.getZ());
		glRotatef(-90, 0, 1, 0);


		//esfera da laranja
		glPushMatrix();
		GLfloat sphereAmb[] = { 0.44f,0.14f,0.0f,1.0f };
		GLfloat sphereDiff[] = { 0.89f,0.57f,0.0f,1.0f };
		GLfloat sphereSpec[] = { 0.11f,0.1f,0.0f,1.0f };
		GLfloat sphereShine = 3;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sphereAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sphereDiff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sphereSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sphereShine);
		glColor3f(1, 0.4, 0);
		glutSolidSphere(1, 25, 15);
		glPopMatrix();

		//ramo
		glPushMatrix();
		GLfloat ramoAmb[] = { 1.0f,0.89f,0.0f,1.0f };
		GLfloat ramoDiff[] = { 0.41f,0.22f,0.0f,1.0f };
		GLfloat ramoSpec[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat ramoShine = 76.8;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ramoAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ramoDiff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ramoSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ramoShine);
		glColor3f(0, 1, 0);
		glTranslatef(1, 0, 0);
		glScalef(1, 1, 3);
		glScalef(1, 1, 0);
		glutSolidSphere(0.2, 25, 25);
		glPopMatrix();

		glPopMatrix();
	}
}