#include "DynamicObject.h"
#define ACCELERATION 6

DynamicObject::DynamicObject()
{
}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::update(double delta_t)
{
	double x_speed;
	double y_speed;
	x_speed = _speed.getX() + delta_t*(ACCELERATION/2);
	y_speed = _speed.getY() + delta_t*(ACCELERATION/2);
}

void DynamicObject::setSpeed(const Vector3 & speed)
{
	_speed = speed;
}

void DynamicObject::setSpeed(double x, double y, double z)
{
	_speed.setXYZ(x, y, z);
}

Vector3 * DynamicObject::getSpeed()
{
	return &_speed;
}
