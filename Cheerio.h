#pragma once
#include "Obstacle.h"
class Cheerio :
	public Obstacle
{
protected:
	bool _collided = false;
	double _currentSpeed, _directionX, _directionY;
public:
	Cheerio();
	Cheerio(double x, double y, double z);
	~Cheerio();

	void setCurrentSpeed(double speed);
	double getCurrentSpeed();

	void setColided(bool boolean);
	bool getColided();

	void setDirectionXY(double x, double y);

	void draw();
	void update(double delta_t);
};
