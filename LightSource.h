#pragma once
#include <GL/glut.h>
#include <gl\gl.h>
#include <gl\glu.h> 
#include <gl\glut.h>
#include "Vector4.h"

class LightSource
{
private:
	Vector3* _direction;
	Vector4* _position;
	Vector4* _ambient;
	Vector4* _diffuse;
	Vector4* _specular;
	Vector3* _attenuation;
	GLfloat* _exponent;
	GLfloat* _cutOff;
	int _id;
	bool _state;

public:
	LightSource(int i);
	~LightSource();
	void setPosition(double x, double y, double z, double w);
	void setDirection(double x, double y, double z);
	void setAmbient(double x, double y, double z, double w);
	void setDiffuse(double x, double y, double z, double w);
	void setSpecular(double x, double y, double z, double w);
	void setExponent(GLfloat* f);
	void setCutOff(GLfloat* f);
	void setAttenuation(double x, double y, double z);
	void setState(bool b);
	int getId();
	bool getState();
	void ignite();
};
