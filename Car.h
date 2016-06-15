#pragma once
#include "DynamicObject.h"

#define PI  3.1415926535897
#define FORWARD_ACCELERATION 0.0006
#define BACKWARDS_ACCELERATION 0.0006
#define MAX_FORWARD_SPEED 0.3
#define MAX_BACKWARDS_SPEED 0.2
#define ANGLE_INCREASE 3
#define FRICTION 0.0005

class Car :
	public DynamicObject
{
protected:
	double _turnAngle = 90, _currentSpeed = 0, _acceleration=0;
	bool upKeyPressed, downKeyPressed, rightKeyPressed, leftKeyPressed, colided=false , active = true;

public:
	Car();
	Car(double x, double y, double z);
	~Car();

	void setAccelaration(double accel);
	void setTurnAngle(double angle);
	void setCurrentSpeed(double speed);
	void setUp(bool b);
	void setDown(bool b);
	void setLeft(bool b);
	void setRight(bool b);
	void setColided(bool boolean);
	void setActive(bool boolean);

	bool getColided();
	bool getUp();
	bool getDown();
	bool getLeft();
	bool getRight();
	double getAcceleration();
	double getCurrentSpeed();
	double getCurrentAngle();
	

	void update(double delta_t);
	void drawWheel();
	void drawCube();
	void draw();
};

