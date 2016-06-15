#include "Vector3.h"


Vector3::Vector3()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3::Vector3(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3::~Vector3()
{
}

double Vector3::getX()
{
	return _x;
}

double Vector3::getY()
{
	return _y;
}

double Vector3::getZ()
{
	return _z;
}

void Vector3::setXYZ(double x, double y, double z)
{
	_x = x; _y = y; _z = z;
}

Vector3 Vector3::operator=(const Vector3 & vec)
{
	_x = vec._x;
	_y = vec._y;
	_z = vec._z;

	return *this;
}

Vector3 Vector3::operator+(const Vector3 & vec)
{
	_x = _x + vec._x;
	_y = _y + vec._y;
	_z = _z + vec._z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3 & vec)
{
	_x = _x - vec._x;
	_y = _y - vec._y;
	_z = _z - vec._z;

	return *this;
}

Vector3 Vector3::operator*(double scalar)
{
	_x = scalar * _x;
	_y = scalar * _y;
	_z = scalar * _z;

	return *this;
}
