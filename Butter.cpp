#include "Butter.h"
#include <GL/glut.h>
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h>


Butter::Butter()
{
}

Butter::Butter(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}


Butter::~Butter()
{
}

void Butter::draw()
{	
	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	GLfloat amb[] = { 0.9f,0.78f,0.0f,1.0f };
	GLfloat diff[] = { 0.51f,0.4f,0.0f,1.0f };
	GLfloat spec[] = { 0.34f,0.49f,0.0f,1.0f };
	GLfloat shine = 52;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glColor3f(0.9, 0.6, 0.0);
	glScalef(1, 1, 0.2);
	glutSolidSphere(0.5, 25, 15);
	glPopMatrix();
}
