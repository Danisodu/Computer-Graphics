#include "LightSource.h"

LightSource::LightSource(int i)
{
	_id = i;
	_position = new Vector4(0, 0, 1, 0);
	_direction = new Vector3(0, 0, -1);
	_ambient = new Vector4(0, 0, 0, 1);
	_diffuse = new Vector4(1, 1, 1, 1); 
	_specular = new Vector4(1, 1, 1, 1);
	_exponent = new GLfloat(0.0);
	_cutOff = new GLfloat(180.0);
	_attenuation = new Vector3(1, 0, 0);
	_state = false;
}

LightSource::~LightSource()
{
}

void LightSource::setPosition(double x, double y, double z, double w) {
	_position->setXYZW(x, y, z, w);
}

void LightSource::setDirection(double x, double y, double z) {
	_direction->setXYZ(x, y, z);
}

void LightSource::setAmbient(double x, double y, double z, double w) {
	_ambient->setXYZW(x, y, z, w);
}

void LightSource::setDiffuse(double x, double y, double z, double w) {
	_diffuse->setXYZW(x, y, z, w);
}

void LightSource::setSpecular(double x, double y, double z, double w) {
	_specular->setXYZW(x, y, z, w);
}

void LightSource::setExponent(GLfloat* f) {
	_exponent = f;
}

void LightSource::setCutOff(GLfloat* f) {
	_cutOff = f;
}

void LightSource::setAttenuation(double x, double y, double z)
{
	_attenuation->setXYZ(x, y, z);
}

void LightSource::setState(bool b) {
	_state = b;
}

int LightSource::getId() {
	return _id;
}

bool LightSource::getState() {
	return _state;
}

void LightSource::ignite() {

	glEnable(GL_LIGHT0 + _id);

	GLfloat position[4] = { _position->getX(), _position->getY(),_position->getZ(),_position->getW() };
	GLfloat direction[3] = { _direction->getX(), _direction->getY(), _direction->getZ() };
	GLfloat ambient[4] = { _ambient->getX(),_ambient->getY(),_ambient->getZ(),_ambient->getW() };
	GLfloat diffuse[4] = { _diffuse->getX(),_diffuse->getY(),_diffuse->getZ(),_diffuse->getW() };
	GLfloat specular[4] = { _specular->getX(),_specular->getY(),_specular->getZ(),_specular->getW() };
	GLfloat attenuation[3] = { _attenuation->getX(), _attenuation->getY(), _attenuation->getZ() };

	glLightfv(GL_LIGHT0 + _id, GL_POSITION, position);
	glLightfv(GL_LIGHT0 + _id, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT0 + _id, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0 + _id, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0 + _id, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0 + _id, GL_SPOT_EXPONENT, _exponent);
	glLightfv(GL_LIGHT0 + _id, GL_SPOT_CUTOFF, _cutOff);
	glLightfv(GL_LIGHT0 + _id, GL_CONSTANT_ATTENUATION, &(attenuation[0]));
	glLightfv(GL_LIGHT0 + _id, GL_LINEAR_ATTENUATION, &(attenuation[1]));
	glLightfv(GL_LIGHT0 + _id, GL_QUADRATIC_ATTENUATION, &(attenuation[2]));
}