#include "Vector4.h"

Vector4::Vector4() {
	Vector3::Vector3();
	_w = 0;
}

Vector4::Vector4(double x, double y, double z, double w)
{
	setXYZW(x, y, z, w);
}

void Vector4::setXYZW(double x, double y, double z, double w){
	Vector3::setXYZ(x, y, z);
	_w = w;
}

double Vector4::getW()
{
	return _w;
}