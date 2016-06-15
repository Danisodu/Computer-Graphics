#pragma once
#include "Obstacle.h"
class Butter :
	public Obstacle
{
public:
	Butter();
	Butter(double x, double y, double z);
	~Butter();

	void draw();
};

