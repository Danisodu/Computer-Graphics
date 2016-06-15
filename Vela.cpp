#pragma once
#include "Vela.h"


void Vela::draw() {

	GLUquadricObj *obj = gluNewQuadric();

	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	glColor3f(0.89f, 0.82f, 0.47f);
	gluCylinder(obj, 0.4, 0.4, 2, 20, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ() + 2);
	glScalef(1, 1, 0);
	glColor3f(0.89f, 0.82f, 0.47f);
	glutSolidSphere(0.4, 20, 40);
	glPopMatrix();
}

