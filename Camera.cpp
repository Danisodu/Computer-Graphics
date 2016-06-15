#include "Camera.h"
#include <GL/glut.h>
#include <gl\gl.h>


Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::visualize()
{
}

void Camera::project()
{
}

void Camera::setEye(double x, double y, double z)
{
	_position.setXYZ(x, y, z);
}

void Camera::setCenter(double x, double y, double z)
{
	_center.setXYZ(x, y, z);
}

void Camera::setUp(double x, double y, double z)
{
	_up.setXYZ(x, y, z);
}
