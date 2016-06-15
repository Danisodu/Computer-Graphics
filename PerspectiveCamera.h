#pragma once
#include "Camera.h"
class PerspectiveCamera :
	public Camera
{
protected:
	double _fovy;
	double _aspect;
	double _ratio;
	double _near;
	double _far;

public:
	PerspectiveCamera();
	~PerspectiveCamera();

	void update(double fovy, double aspect, double near, double far);
	void visualize();
	void project();

};

