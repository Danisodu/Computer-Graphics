#pragma once
#include "Camera.h"
class OrthogonalCamera :
	public Camera
{
protected:
	Vector3 _projectionLowerLimits, _projectionUpperLimits, _target;
public:
	OrthogonalCamera();
	~OrthogonalCamera();

	void update(double left, double right, double bottom, double top, double near, double far);
	void visualize();
	void project();
	void setLowerLimits(double x, double y, double z);
	void setUpperLimits(double x, double y, double z);
};

