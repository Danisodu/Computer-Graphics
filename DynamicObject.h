#pragma once
#include "GameObject.h"
class DynamicObject :
	public GameObject
{

protected:
	Vector3 _speed;
public:
	DynamicObject();
	~DynamicObject();

	virtual void update(double delta_t);

	void setSpeed(const Vector3 & speed);

	void setSpeed(double x, double y, double z);

	Vector3 * getSpeed();



};

