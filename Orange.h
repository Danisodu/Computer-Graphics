#pragma once
#include "DynamicObject.h"
#include "Source.h"
#include "Vector3.h"
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#define MAX_SPEED 0.2
#define ACCELERATION 0.0006
#define ANGLEINCREASE 10
#define SPEEDHIGHERINC 0.025
#define SPEEDLOWERINC 0.01
#define ORANGEINIPOSITION 14
#define PI 3.1415926535897

class Orange :
	public DynamicObject
{

protected:
	double _currentSpeed, _angle = 0;
	int _oldTime = 0, _id;
	Vector3 _direction;
	bool _raiseSpeed = false, _alive, _waitingToLive = false;
public:
	Orange();
	Orange(double x, double y, double z);
	~Orange();
	void setId(int i);
	void setDirection(double x, double y, double z);
	void setAngle(double a);
	void setLifeState(bool b);
	void setSpeedState(bool b);
	void setCurrentSpeed(double s);
	void setWaitingState(bool b);
	int getId();
	double getCurrentSpeed();
	bool getSpeedState();
	bool getWaitingState();
	double generateNumber(double max, double min);
	double generatePosition(int quadrante, int axis);
	void update(double delta_t);
	void draw();
};