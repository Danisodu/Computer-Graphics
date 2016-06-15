#include "OrthogonalCamera.h"
#include <GL/glut.h>
#include <gl\gl.h>


OrthogonalCamera::OrthogonalCamera()
{
}


OrthogonalCamera::~OrthogonalCamera()
{
}

void OrthogonalCamera::update(double left, double right, double bottom, double top, double near, double far)
{
	_projectionLowerLimits.setXYZ(left, bottom, near);
	_projectionUpperLimits.setXYZ(right, top, far);
}

void OrthogonalCamera::visualize()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
		_center.getX(), _center.getY(), _center.getZ(),
		_up.getX(), _up.getY(), _up.getZ());
}

void OrthogonalCamera::project()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(_projectionLowerLimits.getX(), _projectionUpperLimits.getX(),
		_projectionLowerLimits.getY(), _projectionUpperLimits.getY(),
		_projectionLowerLimits.getZ(), _projectionUpperLimits.getZ());
}

void OrthogonalCamera::setLowerLimits(double x, double y, double z)
{
	_projectionLowerLimits.setXYZ(x, y, z);
}

void OrthogonalCamera::setUpperLimits(double x, double y, double z)
{
	_projectionUpperLimits.setXYZ(x, y, z);
}

