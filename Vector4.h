#pragma once
#include "Vector3.h"

class Vector4 : 
	public Vector3
{
protected:
	double _w;

public:
	Vector4();
	Vector4(double x, double y, double z, double w);
	~Vector4(){}

	void setXYZW(double x, double y, double z, double w);

	double getW();

};
