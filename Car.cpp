#include "Car.h"
#include "stdlib.h"
#include <GL/glut.h>
#include <gl\gl.h> 
#include <gl\glu.h>
#include <cmath>
#include <iostream>
#include <gl\glut.h>



Car::Car()
{
}

Car::Car(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}


Car::~Car()
{
}

void Car::setAccelaration(double accel)
{
	_acceleration = accel;
}

void Car::setTurnAngle(double angle)
{
	_turnAngle = angle;
}

void Car::setCurrentSpeed(double speed)
{
	_currentSpeed = speed;
}

void Car::setUp(bool b)
{
	upKeyPressed = b;
}

void Car::setLeft(bool b)
{
	leftKeyPressed = b;
}

void Car::setRight(bool b)
{
	rightKeyPressed = b;
}

void Car::setColided(bool boolean)
{
	colided = boolean;
}

void Car::setActive(bool boolean)
{
	active = boolean;
}

void Car::setDown(bool b)
{
	downKeyPressed = b;
}

bool Car::getColided()
{
	return colided;
}

bool Car::getUp()
{
	return upKeyPressed;
}

bool Car::getDown()
{
	return downKeyPressed;
}

bool Car::getLeft()
{
	return leftKeyPressed;
}

bool Car::getRight()
{
	return rightKeyPressed;
}

double Car::getAcceleration()
{
	return _acceleration;
}

double Car::getCurrentSpeed()
{
	return _currentSpeed;
}

double Car::getCurrentAngle()
{
	return _turnAngle;
}

void Car::update(double delta_t) {
	bool pressed = false;
	_acceleration = 0;
	Vector3 speed(cos((_turnAngle)*(PI / 180)), sin((_turnAngle)*(PI / 180)), 0);

	if (upKeyPressed) {
		pressed = true;
		_acceleration = FORWARD_ACCELERATION;
		if (_currentSpeed + (delta_t * _acceleration) < MAX_FORWARD_SPEED) {
			_currentSpeed = _currentSpeed + (delta_t * _acceleration);
		}
		else {
			_currentSpeed = MAX_FORWARD_SPEED;
		}
	}
	else if (downKeyPressed) {
		pressed = true;
		_acceleration = -BACKWARDS_ACCELERATION;
		if (_currentSpeed + (delta_t * _acceleration) > -MAX_BACKWARDS_SPEED) {
			_currentSpeed = _currentSpeed + (delta_t * _acceleration);
		}
		else {
			_currentSpeed = -MAX_BACKWARDS_SPEED;
		}
	}
	if (leftKeyPressed) {
		_turnAngle += ANGLE_INCREASE;
	}
	if (rightKeyPressed) {
		_turnAngle -= ANGLE_INCREASE;
	}
	if (!pressed) {
		if (_currentSpeed > 0) {
			if (_currentSpeed - (delta_t)* 0.0005 > 0) {
				_currentSpeed -= (delta_t)* 0.0005;
			}
			else {
				_currentSpeed = 0;
			}
		}
		else if (_currentSpeed < 0) {
			if (_currentSpeed + (delta_t)* FRICTION < 0) {
				_currentSpeed += (delta_t)* FRICTION;
			}
			else {
				_currentSpeed = 0;
			}
		}
	}

	_speed = speed * _currentSpeed;
	_position = (_position + _speed);
}

void Car::drawCube()
{
	//up
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();

	//down
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, -1.0f, 0.0f);

	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();

	//right
	glBegin(GL_POLYGON);

	glNormal3f(1.0f, 0.0f, 0.0f);

	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glEnd();

	//left
	glBegin(GL_POLYGON);

	glNormal3f(-1.0f, 0.0f, 0.0f);

	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	//near
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	//far
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}

void Car::drawWheel()
{
	//front
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.25f, 0.5f, 0.05f);
	glVertex3f(0.5f, 0.0f, 0.05f);
	glVertex3f(0.25f, -0.5f, 0.05f);
	glVertex3f(-0.25f, -0.5f, 0.05f);
	glVertex3f(-0.5f, 0.0f, 0.05f);
	glVertex3f(-0.25f, 0.5f, 0.05f);

	glEnd();

	//back
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(0.25f, 0.5f, -0.05f);
	glVertex3f(0.5f, 0.0f, -0.05f);
	glVertex3f(0.25f, -0.5f, -0.05f);
	glVertex3f(-0.25f, -0.5f, -0.05f);
	glVertex3f(-0.5f, 0.0f, -0.05f);
	glVertex3f(-0.25f, 0.5f, -0.05f);

	glEnd();

	//1 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.25f, 0.5f, 0.05f);
	glVertex3f(0.5f, 0.0f, 0.05f);
	glVertex3f(0.25f, 0.5f, -0.05f);
	glVertex3f(0.5f, 0.0f, -0.05f);

	glEnd();

	//2 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(1.0f, -1.0f, 0.0f);

	glVertex3f(0.5f, 0.0f, 0.05f);
	glVertex3f(0.25f, -0.5f, 0.05f);
	glVertex3f(0.5f, 0.0f, -0.05f);
	glVertex3f(0.25f, -0.5f, -0.05f);

	glEnd();

	//3 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.25f, -0.5f, 0.05f);
	glVertex3f(-0.25f, -0.5f, 0.05f);
	glVertex3f(0.25f, -0.5f, -0.05f);
	glVertex3f(-0.25f, -0.5f, -0.05f);

	glEnd();

	//4 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, -1.0f, 0.0f);

	glVertex3f(-0.25f, -0.5f, 0.05f);
	glVertex3f(-0.5f, 0.0f, 0.05f);
	glVertex3f(-0.25f, -0.5f, -0.05f);
	glVertex3f(-0.5f, 0.0f, -0.05f);

	glEnd();

	//5 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(-1.0f, 1.0f, 0.0f);

	glVertex3f(-0.5f, 0.0f, 0.05f);
	glVertex3f(-0.25f, 0.5f, 0.05f);
	glVertex3f(-0.5f, 0.0f, -0.05f);
	glVertex3f(-0.25f, 0.5f, -0.05f);

	glEnd();

	//6 rectangle
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(-0.25f, 0.5f, 0.05f);
	glVertex3f(0.25f, 0.5f, 0.05f);
	glVertex3f(-0.25f, 0.5f, -0.05f);
	glVertex3f(0.25f, 0.5f, -0.05f);

	glEnd();
}

void Car::draw()
{
	if (!active) return;
	// Reinicia transformações
	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ() + 0.2);
	glRotatef(_turnAngle, 0, 0, 1);

	//corpo do carro
	glPushMatrix();
	GLfloat bodyAmb[] = { 0.35f,0.0f,0.0f,1.0f };
	GLfloat bodyDiff[] = { 0.69f,0.0f,0.0f,1.0f };
	GLfloat bodySpec[] = { 0.29f,0.28f,0.29f,1.0f };
	GLfloat bodyShine = 46;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodyDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodySpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bodyShine);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(1.0f, 0.8f, 0.3f);
	drawCube();
	glPopMatrix();

	//cockpit do carro
	glPushMatrix();
	glTranslatef(-0.2f, 0.0f, 0.20f);
	glScalef(0.4f, 0.6f, 0.1f);
	GLfloat cockpitAmb[] = { 0.07f,0.07f,0.07f,1.0f };
	GLfloat cockpitDiff[] = { 0.13f,0.17f,0.17f,1.0f };
	GLfloat cockpitSpec[] = { 0.42f,0.41f,0.41f,1.0f };
	GLfloat cockpitShine = 4;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cockpitAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cockpitDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cockpitSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cockpitShine);
	glColor3f(1.0, 1.0, 1.0);
	drawCube();
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();


	// roda traseira direita
	glPushMatrix();
	GLfloat wheel1Amb[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat wheel1Diff[] = { 0.13f,0.13f,0.14f,1.0f };
	GLfloat wheel1Spec[] = { 0.17f,0.18f,0.19f,1.0f };
	GLfloat wheel1Shine = 12;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wheel1Amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheel1Diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wheel1Spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wheel1Shine);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.3f, -0.45f, 0.0f);
	glRotated(90, 1, 0, 0);
	glScalef(0.4f, 0.4f, 1.5f);
	drawWheel();
	glColor3f(0, 0, 0);
	glutWireTorus(0.05, 0.2, 32, 32);
	glPopMatrix();


	//perna dianteira direita
	glPushMatrix();
	GLfloat wheel2Amb[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat wheel2Diff[] = { 0.13f,0.13f,0.14f,1.0f };
	GLfloat wheel2Spec[] = { 0.17f,0.18f,0.19f,1.0f };
	GLfloat wheel2Shine = 12;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wheel2Amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheel2Diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wheel2Spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wheel2Shine);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.3f, -0.45f, 0.0);
	glRotated(90, 1, 0, 0);
	glScalef(0.4f, 0.4f, 1.5f);
	drawWheel();
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(0.05, 0.2, 32, 32);
	glPopMatrix();


	// roda traseira direita
	glPushMatrix();
	GLfloat wheel3Amb[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat wheel3Diff[] = { 0.13f,0.13f,0.14f,1.0f };
	GLfloat wheel3Spec[] = { 0.17f,0.18f,0.19f,1.0f };
	GLfloat wheel3Shine = 12;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wheel3Amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheel3Diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wheel3Spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wheel3Shine);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.3f, 0.45f, 0.0f);
	glRotated(90, 1, 0, 0);
	glScalef(0.4f, 0.4f, 1.5f);
	drawWheel();
	glColor3f(0, 0, 0);
	glutWireTorus(0.05, 0.2, 32, 32);
	glPopMatrix();


	//perna dianteira direita
	glPushMatrix();
	GLfloat wheel4Amb[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat wheel4Diff[] = { 0.13f,0.13f,0.14f,1.0f };
	GLfloat wheel4Spec[] = { 0.17f,0.18f,0.19f,1.0f };
	GLfloat wheel4Shine = 12;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wheel4Amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheel4Diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wheel4Spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wheel4Shine);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.3f, 0.45f, 0.0);
	glRotated(90, 1, 0, 0);
	glScalef(0.4f, 0.4f, 1.5f);
	drawWheel();
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(0.05, 0.2, 32, 32);
	glPopMatrix();

	glPopMatrix();
}
