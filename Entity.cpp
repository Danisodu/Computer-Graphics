#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

Vector3 * Entity::getPosition()
{
	return &_position;
}

Vector3 * Entity::setPosition(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
	return &_position;
}

Vector3 * Entity::setPosition(const Vector3 & vec)
{
	_position = vec;
	return &_position;
}
