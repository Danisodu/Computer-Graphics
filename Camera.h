#pragma once
#include "Entity.h"
class Camera :
	public Entity
{
protected:
	Vector3 _center, _up;
public:
	Camera();
	~Camera();

	virtual void visualize();
	virtual void project();
	void setEye(double x, double y , double z);
	void setCenter(double x, double y, double z);
	void setUp(double x, double y, double z);

};

