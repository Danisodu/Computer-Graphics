#pragma once

#include <list>
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "GameObject.h"
#include "LightSource.h"
#include "Car.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Vela.h"
#include "Texture.h"
#include "Plane.h"
#define CAR_RADIUS 0.6
#define CHEERIO_RADIUS 0.25
#define ORANGE_RADIUS 1
#define BUTTER_RADIUS 0.5

#define OUTTER_ANGLE_INCREASE 360/40
#define INNER_ANGLE_INCREASE 360/20
#define OUTTERLENGTH 14
#define INNERLENGTH 10

#define SPEEDHIGHERINI 0.045
#define SPEEDLOWERINI 0.03
#define NQUADRANTES 4
#define NORANGES 3
#define ORANGEINIPOSITION 14
#define PI 3.1415926535897

#define CAR_CAMERA_DISTANCE 6

#define SPEED_SCALAR 1.5

class GameManager
{

protected:
	int _oldTimeSinceStart = 0, _lifes = 5;
	bool  wireFlag, fieldFlag, carFlag, orthoFlag = true, dirLightFlag, spotLightFlag,
		pointLightFlag, activateLights, shadeFlag, pauseFlag, startFlag, initIsDone = false;
	Car * _car;
	Camera * _activeCamera;
	OrthogonalCamera * _2dCamera;
	OrthogonalCamera * _guiCamera;
	PerspectiveCamera * _fieldCamera;
	PerspectiveCamera * _carCamera;
	std::list<GameObject*> _gameObjects;
	std::vector<Orange*> _oranges;
	std::vector<LightSource*> _lightSources;
	std::vector<Car*> _lifeVector;
	//Texture* _pauseTex;
	//Texture* _gameOverTex;
	Plane* _pausePlane;
	Plane* _gameOverPlane;


public:
	GameManager();
	~GameManager();

	void display();
	void reshape(int w, int h);
	void keyPressed(int key, int x, int y);
	void keyReleased(int key, int x, int y);
	void keyAPressed(unsigned char key, int x, int y);
	void raiseOrangeSpeed();
	void resetOrange(int i);
	void onTimer();
	void idle();
	void update();
	void init();
	void car_Respawn(Car car);
	void car_Colider_Butter(Car car);
	void car_Colider_Cheerio();
	void cheerio_Colider(Cheerio * cheerio);
	void collision(Car* car, GameObject* obj);
	void orangeCollision(Orange * orange);
	void gameOver();
	double generateNumber(double max, double min);
	double generatePosition(int quadrante, int axis);
};