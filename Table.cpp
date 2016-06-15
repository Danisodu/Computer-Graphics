#include "Table.h"
#include "Texture.h"
#define SQUARES 10
#define CUBESIZE 3
#define TABLESIZE 30
#define TRANSLATION 3

Table::Table()
{
}

Table::Table(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

Table::~Table()
{
}

/*
void Table::setTexture(Texture* t) {
	_tex = t;
}*/

void Table::drawTopTable()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(1.5f, 1.5f, 0.5f); //top right
	
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(1.5f, -1.5f, 0.5f); // bottom right

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-1.5f, -1.5f, 0.5f); // bottom left

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-1.5f, 1.5f, 0.5f); //top left

	glEnd();

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}

void Table::draw()
{
	if (_doItRightFlag){
		_tex = new Texture("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\wood.png");
		_doItRightFlag = false;
	}
	_tex->bind();

	GLfloat amb[] = { 0.87f,0.72f,0.25f,0.53f };
	GLfloat diff[] = { 0.0f,0.5f,0.8f,1.0f };
	GLfloat spec[] = { 0.0f,0.2f,0.5f,1.0f };
	GLfloat shine = 15;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	//////////////// QUADRADOS DA MESA ///////////////

	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());

	for (int i = 0; i < SQUARES; i++) {
		for (int j = 0; j < SQUARES; j++) {
			glPushMatrix();
			//TABLESIZE / 2 - CUBESIZE / 2 = 13.5
			glTranslatef(-13.5 + TRANSLATION*j, 13.5 - TRANSLATION*i, 1.0);
			drawTopTable();
			glPopMatrix();
		}
	}

	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}