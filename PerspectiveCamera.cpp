#include "PerspectiveCamera.h"
#include <GL/glut.h>
#include <gl\gl.h>



PerspectiveCamera::PerspectiveCamera()
{
}


PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::update(double fovy, double aspect, double near, double far)
{
	_fovy = fovy;
	_aspect = aspect;
	_near = near;
	_far = far;
}

void PerspectiveCamera::visualize()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
		_center.getX(), _center.getY(), _center.getZ(),
		_up.getX(), _up.getY(), _up.getZ());
}

void PerspectiveCamera::project()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fovy, _aspect, _near, _far);
}
