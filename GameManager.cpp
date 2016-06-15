#include "GameManager.h"
#include "Source.h"
#include "Car.h"
#include "OrthogonalCamera.h"
#include "Butter.h"
#include "Orange.h"
#include <list>
#include "Table.h"
#include "Roadside.h"
#include <GL/glut.h>
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h>
#include "Vector3.h"
#include <math.h>
#include <iostream>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	delete _2dCamera;
	delete _fieldCamera;
	delete _carCamera;
	delete _pausePlane;

	for (auto object : _gameObjects) {
		delete object;
	}

	for (auto object : _lightSources) {
		glDisable(GL_LIGHT0 + object->getId());
		delete object;
	}
}

void GameManager::display()
{
	if (!initIsDone) return;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_activeCamera->project();
	glPushMatrix();
	_activeCamera->visualize();

	for (auto light : _lightSources) {
		if (light->getState()) {
			(light)->ignite();
		}
	}

	for (auto object : _gameObjects) {
		(object)->draw();
	}

	glPopMatrix();


	_guiCamera->project();
	glPushMatrix();
	_guiCamera->visualize();
	glDisable(GL_LIGHTING);
	for (auto life : _lifeVector) {
		life->draw();
	}

	if (pauseFlag) {
		_pausePlane->draw();
	}

	if (_lifes == 0) {
		_gameOverPlane->draw();
	}


	glEnable(GL_LIGHTING);
	glPopMatrix();
	glFlush();
}

void GameManager::reshape(int w, int h)
{
	if (!initIsDone) return;

	float xmin = -15.0, xmax = 15.0, ymin = -15, ymax = 15;
	float ratio = (xmax - xmin) / (ymax - ymin);
	float aspect = (float)w / h;

	if (aspect > ratio)
		glViewport((w - h*ratio) / 2, 0, h*ratio, h);
	else
		glViewport(0, (h - w / ratio) / 2, w, w / ratio);
	_carCamera->update(60, ratio, 0.1, 120);
	_fieldCamera->update(60, ratio, 0.1, 120);
	_2dCamera->update(xmin, xmax, ymin, ymax, -15, 15);

	_activeCamera->project();
	_activeCamera->visualize();

}

void GameManager::keyAPressed(unsigned char key, int x, int y)
{

	if (key == 'a' || key == 'A') {
		wireFlag = !wireFlag;
	}

	if (key == '1' || key == '!') {
		orthoFlag = true;
		carFlag = false;
		fieldFlag = false;
	}

	if (key == '2' || key == '"') {
		orthoFlag = false;
		carFlag = false;
		fieldFlag = true;
	}

	if (key == '3' || key == '#') {
		orthoFlag = false;
		carFlag = true;
		fieldFlag = false;
	}

	if (key == 'n' || key == 'N') {
		dirLightFlag = !dirLightFlag;
	}

	if (key == 'l' || key == 'L') {
		activateLights = !activateLights;
	}

	if (key == 'g' || key == 'G') {
		shadeFlag = !shadeFlag;
	}

	if (key == 'c' || key == 'C') {
		pointLightFlag = !pointLightFlag;
	}

	if (key == 's' || key == 'S') {
		pauseFlag = !pauseFlag;
	}

	if (key == 'r' || key == 'R') {
		startFlag = !startFlag;
	}

	if (key == 'h' || key == 'H') {
		spotLightFlag = !spotLightFlag;
	}
}

void GameManager::keyPressed(int key, int x, int y)
{
	if (!_car->getColided()) {
		switch (key) {
		case GLUT_KEY_RIGHT:
			_car->setRight(true);
			break;

		case GLUT_KEY_LEFT:
			_car->setLeft(true);
			break;

		case GLUT_KEY_UP:
			_car->setUp(true);
			break;

		case GLUT_KEY_DOWN:
			_car->setDown(true);
			break;

		default:
			break;
		}
	}
}

void GameManager::keyReleased(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_RIGHT:
		_car->setRight(false);
		break;

	case GLUT_KEY_LEFT:
		_car->setLeft(false);
		break;

	case GLUT_KEY_UP:
		_car->setUp(false);
		_car->setColided(false);
		break;

	case GLUT_KEY_DOWN:
		_car->setDown(false);
		_car->setColided(false);
		break;

	default:
		break;
	}
}

void GameManager::onTimer()
{
	if (!pauseFlag && initIsDone) {
		update();
	}

	glutPostRedisplay();
}

void GameManager::idle()
{
}

void GameManager::update()
{
	if (!initIsDone) return;

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - _oldTimeSinceStart;
	_oldTimeSinceStart = timeSinceStart;

	if (startFlag) {
		gameOver();
		return;
	}

	if (wireFlag) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (orthoFlag) {
		_activeCamera = _2dCamera;
	}

	if (fieldFlag) {
		_activeCamera = _fieldCamera;
	}

	if (carFlag) {
		_activeCamera = _carCamera;
	}

	if (activateLights) {
		glDisable(GL_LIGHTING);
	}

	else {
		glEnable(GL_LIGHTING);
	}

	if (dirLightFlag) {
		dirLightFlag = false;
		if (_lightSources.size() != 0) {
			_lightSources[0]->setState(!_lightSources[0]->getState());
			if (!_lightSources[0]->getState())
				glDisable(GL_LIGHT0 + _lightSources[0]->getId());
		}
	}

	if (spotLightFlag) {
		spotLightFlag = false;
		if (_lightSources.size() != 0) {
			_lightSources[7]->setState(!_lightSources[7]->getState());

			if (!_lightSources[7]->getState())
				glDisable(GL_LIGHT0 + _lightSources[7]->getId());
		}
	}

	if (shadeFlag) {
		glShadeModel(GL_FLAT);
	}

	else {
		glShadeModel(GL_SMOOTH);
	}

	if (pointLightFlag) {
		pointLightFlag = !pointLightFlag;
		if (_lightSources.size() != 0) {
			for (int i = 1; i < 7; i++) {
				_lightSources[i]->setState(!_lightSources[i]->getState());

				if (!_lightSources[i]->getState())
					glDisable(GL_LIGHT0 + _lightSources[i]->getId());
			}
		}
	}

	if (_gameObjects.size()) {
		for (auto object : _gameObjects) {
			object->update((double)deltaTime);
			collision(_car, object);
		}
	}

	if (_oranges.size() != 0) {
		for (auto object : _oranges) {
			orangeCollision(object);
		}
	}

	_carCamera->setEye(_car->getPosition()->getX() - (CAR_CAMERA_DISTANCE * (cos(_car->getCurrentAngle() * (PI / 180)))),
		_car->getPosition()->getY() - (CAR_CAMERA_DISTANCE * (sin(_car->getCurrentAngle() * (PI / 180)))),
		CAR_CAMERA_DISTANCE);
	_carCamera->setCenter(_car->getPosition()->getX(), _car->getPosition()->getY(), _car->getPosition()->getZ());

	if (_lightSources.size() != 0) {
		_lightSources[7]->setPosition(_car->getPosition()->getX() + 0.5*cos(_car->getCurrentAngle()*(PI / 180)), _car->getPosition()->getY()
			+ 0.5*sin(_car->getCurrentAngle()*(PI / 180)), _car->getPosition()->getZ(), 1.0);
		_lightSources[7]->setDirection(cos(_car->getCurrentAngle() * (PI / 180)), sin(_car->getCurrentAngle() * (PI / 180)), 0);
	}
}

void GameManager::car_Respawn(Car car)
{
	if (!initIsDone) return;
	_car->setRight(false);
	_car->setLeft(false);
	_car->setUp(false);
	_car->setDown(false);
	_car->setTurnAngle(90);
	_car->setCurrentSpeed(0);
	_car->setPosition(-12, 0, 1.7);
	_lifes--;

	if (_lifeVector.size() != 0) {
		_lifeVector[_lifes]->setActive(false);
	}
}

void GameManager::car_Colider_Butter(Car car)
{

	_car->setCurrentSpeed(0);
}

void GameManager::car_Colider_Cheerio()
{

	_car->setColided(true);

	if (_car->getCurrentSpeed() > 0) {
		_car->setCurrentSpeed(-0.2);
		return;
	}

	if (_car->getCurrentSpeed() < 0) {
		_car->setCurrentSpeed(0.2);
		return;
	}
}

void GameManager::cheerio_Colider(Cheerio * cheerio)
{

	cheerio->setColided(true);
	cheerio->setCurrentSpeed(abs(_car->getCurrentSpeed()*SPEED_SCALAR));
	cheerio->setDirectionXY(_car->getSpeed()->getX(),
		_car->getSpeed()->getY());
}


void GameManager::collision(Car * car, GameObject * obj)
{

	double distance, dx, dy;

	dx = (_car->getPosition()->getX() - obj->getPosition()->getX());
	dy = (_car->getPosition()->getY() - obj->getPosition()->getY());

	distance = sqrt(dx*dx + dy*dy);

	if (_car->getPosition()->getX() < -15 || _car->getPosition()->getX() > 15 ||
		_car->getPosition()->getY() < -15 || _car->getPosition()->getY() > 15) {
		car_Respawn(*car);
	}

	if (Cheerio* cheerio = dynamic_cast<Cheerio*>(obj)) {

		if (CAR_RADIUS + CHEERIO_RADIUS >= distance) {
			cheerio_Colider(cheerio);
			car_Colider_Cheerio();
			_car->setUp(false);
			_car->setDown(false);
		}
	}

	if (Orange* orange = dynamic_cast<Orange*>(obj)) {

		if (CAR_RADIUS + ORANGE_RADIUS >= distance) {
			car_Respawn(*car);
		}
	}

	if (Butter* butter = dynamic_cast<Butter*>(obj)) {

		if (CAR_RADIUS + BUTTER_RADIUS >= distance) {

			car_Colider_Butter(*car);
		}
	}
}

void GameManager::orangeCollision(Orange * orange)
{

	if ((orange->getPosition()->getX() < -16 || orange->getPosition()->getX() > 16 ||
		orange->getPosition()->getY() < -16 || orange->getPosition()->getY() > 16)
		&& !orange->getWaitingState()) {
		glutTimerFunc(2000, reAlive, orange->getId());
		orange->setLifeState(false);
		orange->setWaitingState(true);
	}
}

double GameManager::generateNumber(double max, double min)
{

	double n = (max - (min)) * ((double)rand() / (double)RAND_MAX) + (min);
	return n;
}

void GameManager::raiseOrangeSpeed()
{

	if (!pauseFlag) {
		for (auto object : _oranges) {
			(object)->setSpeedState(true);
		}
	}
}

void GameManager::resetOrange(int i)
{

	int quadrante = rand() % NQUADRANTES;
	double dir = generateNumber(365, 1);

	Orange *o = _oranges[i];

	if (!pauseFlag) {
		if ((o->getSpeedState() == true) && o->getCurrentSpeed() <= MAX_SPEED) {
			o->setCurrentSpeed(generateNumber(o->getCurrentSpeed() + SPEEDHIGHERINC, o->getCurrentSpeed() + SPEEDLOWERINC));
			o->setSpeedState(false);
		}

		o->setPosition(generatePosition(quadrante, 0), generatePosition(quadrante, 1), 2.6);
		o->setDirection(cos(dir*(PI / 180)), sin(dir*(PI / 180)), 0);
		o->setAngle(0);
		o->setLifeState(true);
	}

	o->setWaitingState(false);
}

double GameManager::generatePosition(int quadrante, int axis)
{

	switch (quadrante) {
	case 0:
		if (axis == 0) { return -ORANGEINIPOSITION; } //14 para ela aparecer inteira na mesa, 15 - raio = 14
													  //axis=0 para o X, axis=1 para o Y
		else { return generateNumber(15, -15); }

	case 1:
		if (axis == 0) { return generateNumber(15, -15); }

		else { return ORANGEINIPOSITION; }

	case 2:
		if (axis == 0) { return ORANGEINIPOSITION; }

		else {
			return generateNumber(15, -15);
		}

	case 3:
		if (axis == 0) { return generateNumber(15, -15); }

		else { return -ORANGEINIPOSITION; }

	default:
		return -1;
	}
}

void GameManager::gameOver()
{
	initGame();
}

void GameManager::init()
{
	int quadrante;
	double direction;

	std::srand(std::time(0));


	//Initializing Flags
	wireFlag = false;
	dirLightFlag = false;
	spotLightFlag = false;
	pointLightFlag = false;
	activateLights = false;
	shadeFlag = false;
	pauseFlag = false;
	startFlag = false;


	//Constructing Textures
	//_pauseTex = new Texture("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\pause.jpg");
	//_gameOverTex = new Texture("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\gameover.jpg");

	_pausePlane = new Plane(0, 0, 10);
	_pausePlane->setFileName("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\pause.png");
	_gameOverPlane = new Plane(0, 0, 10);
	_gameOverPlane->setFileName("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\rip.png");
	
	//Constructing Objects//
	Table * table = new Table();
	table->setPosition(0, 0, 0);
	//table->setTexture("C:\\Users\\DanielaD\\Desktop\\MicroMachines CG\\wood.png");
	_gameObjects.push_back(table);

	Roadside * roadside = new Roadside();
	roadside->setPosition(0, 0, 0.05);
	_gameObjects.push_back(roadside);


	//criar a posicao de cada cheerio (outer road)
	int angle = 0;
	double x, y;

	while (angle < 360) {
		x = OUTTERLENGTH * cos((angle)*(PI / 180));
		y = OUTTERLENGTH * sin((angle)*(PI / 180));

		Cheerio *cNew = new Cheerio(x, y, 1.6);
		roadside->insertCheerio(cNew);
		_gameObjects.push_back(cNew);
		angle += OUTTER_ANGLE_INCREASE;
	}

	//criar a posicao de cada cheerio (inner road)
	angle = 0;

	while (angle < 360) {
		x = INNERLENGTH * cos((angle)*(PI / 180));
		y = INNERLENGTH * sin((angle)*(PI / 180));

		Cheerio *cNew = new Cheerio(x, y, 1.6);
		roadside->insertCheerio(cNew);
		_gameObjects.push_back(cNew);
		angle += INNER_ANGLE_INCREASE;
	}

	_car = new Car();
	_car->setPosition(-12, 0, 1.7);
	_car->setRight(false);
	_car->setLeft(false);
	_car->setUp(false);
	_car->setDown(false);
	_gameObjects.push_back(_car);

	x = -14, y = -14;
	for (int i = 0; i < _lifes; i++) {
		Car* tempLife = new Car();
		tempLife->setPosition(x, y, 10);
		tempLife->setRight(false);
		tempLife->setLeft(false);
		tempLife->setUp(false);
		tempLife->setDown(false);
		_lifeVector.push_back(tempLife);
		x += 1.5;
	}


	Butter * butter1 = new Butter();
	butter1->setPosition(3, 12, 1.6);
	_gameObjects.push_back(butter1);

	Butter * butter2 = new Butter();
	butter2->setPosition(4, 13, 1.6);
	_gameObjects.push_back(butter2);

	Butter * butter3 = new Butter();
	butter3->setPosition(5, 12, 1.6);
	_gameObjects.push_back(butter3);

	Butter * butter4 = new Butter();
	butter4->setPosition(-3, -10, 1.6);
	_gameObjects.push_back(butter4);

	Butter * butter5 = new Butter();
	butter5->setPosition(-2, -11, 1.6);
	_gameObjects.push_back(butter5);


	for (int i = 0; i < NORANGES; i++) {

		Orange * orange = new Orange();

		quadrante = rand() % NQUADRANTES;
		direction = generateNumber(365, 1);

		orange->setId(i);
		orange->setPosition(generatePosition(quadrante, 0), generatePosition(quadrante, 1), 2.5);
		orange->setCurrentSpeed(generateNumber(SPEEDHIGHERINI, SPEEDLOWERINI));
		orange->setDirection(cos(direction*(PI / 180)), sin(direction*(PI / 180)), 0);
		orange->setLifeState(true);

		_gameObjects.push_back(orange);
		_oranges.push_back(orange);
	}


	//Constructing Camera
	_2dCamera = new OrthogonalCamera();
	_2dCamera->setEye(0, 0, 15);
	_2dCamera->setCenter(0, 0, 1);
	_2dCamera->setUp(0, 1, 0);
	_2dCamera->setLowerLimits(-15, -15, -15);
	_2dCamera->setUpperLimits(15, 15, 15);
	_activeCamera = _2dCamera;

	_guiCamera = new OrthogonalCamera();
	_guiCamera->setEye(0, 0, 20);
	_guiCamera->setCenter(0, 0, 1);
	_guiCamera->setUp(0, 1, 0);
	_guiCamera->setLowerLimits(-15, -15, -15);
	_guiCamera->setUpperLimits(15, 15, 15);

	_fieldCamera = new PerspectiveCamera();
	_fieldCamera->setEye(-20, -20, 20);
	_fieldCamera->setCenter(0, 0, 2);
	_fieldCamera->setUp(20, 20, 19);
	_fieldCamera->update(90, 1, 0.01, 150);

	_carCamera = new PerspectiveCamera();
	_carCamera->setEye(_car->getPosition()->getX() - (CAR_CAMERA_DISTANCE * (cos(_car->getCurrentAngle() * (PI / 180)))),
		_car->getPosition()->getY() - (CAR_CAMERA_DISTANCE * (sin(_car->getCurrentAngle() * (PI / 180)))),
		CAR_CAMERA_DISTANCE);
	_carCamera->setCenter(_car->getPosition()->getX(), _car->getPosition()->getY(), _car->getPosition()->getZ());
	//_carCamera->setUp(_car->getSpeed()->getX(), _car->getSpeed()->getY(), _car->getSpeed()->getZ());
	_carCamera->setUp(0, 0, 1);
	_carCamera->update(60, 1, 0.01, 150);


	//Constructing light sources

	Vela* vela1 = new Vela();
	vela1->setPosition(-6, 6, 1.6);
	_gameObjects.push_back(vela1);

	Vela* vela2 = new Vela();
	vela2->setPosition(6, 6, 1.6);
	_gameObjects.push_back(vela2);

	Vela* vela3 = new Vela();
	vela3->setPosition(0, -6, 1.6);
	_gameObjects.push_back(vela3);

	Vela* vela4 = new Vela();
	vela4->setPosition(-10, -10, 1.6);
	_gameObjects.push_back(vela4);

	Vela* vela5 = new Vela();
	vela5->setPosition(10, -10, 1.6);
	_gameObjects.push_back(vela5);

	Vela* vela6 = new Vela();
	vela6->setPosition(0, 14, 1.6);
	_gameObjects.push_back(vela6);


	LightSource* daylight = new LightSource(0);
	daylight->setPosition(0, 0, 10, 0);
	daylight->setAmbient(0.5, 0.5, 0.5, 1);
	daylight->setDiffuse(1, 1, 1, 1);
	daylight->setSpecular(1, 1, 1, 1);
	_lightSources.push_back(daylight);

	LightSource* candle1 = new LightSource(1);
	candle1->setPosition(-6, 6, 1, 1);
	candle1->setAmbient(0.7, 0.7, 0.7, 1);
	candle1->setDiffuse(1, 1, 1, 1);
	candle1->setSpecular(1, 1, 1, 1);
	candle1->setAttenuation(1, 0, 0.1);
	_lightSources.push_back(candle1);

	LightSource* candle2 = new LightSource(2);
	candle2->setPosition(6, 6, 1, 1);
	candle2->setAmbient(0.7, 0.7, 0.7, 1);
	candle2->setDiffuse(1, 1, 1, 1);
	candle2->setSpecular(1, 1, 1, 1);
	candle2->setAttenuation(1, 0, 0.1);
	_lightSources.push_back(candle2);

	LightSource* candle3 = new LightSource(3);
	candle3->setPosition(0, -6, 1, 1);
	candle3->setAmbient(0.7, 0.7, 0.7, 1);
	candle3->setDiffuse(1, 1, 1, 1);
	candle3->setSpecular(1, 1, 1, 1);
	candle3->setAttenuation(1, 0, 0.1);
	_lightSources.push_back(candle3);

	LightSource* candle4 = new LightSource(4);
	candle4->setPosition(-10, -10, 1, 1);
	candle4->setAmbient(0.7, 0.7, 0.7, 1);
	candle4->setDiffuse(1, 1, 1, 1);
	candle4->setSpecular(1, 1, 1, 1);
	candle4->setAttenuation(1, 0, 0.1);
	_lightSources.push_back(candle4);

	LightSource* candle5 = new LightSource(5);
	candle5->setPosition(10, -10, 1, 1);
	candle5->setAmbient(0.7, 0.7, 0.7, 1);
	candle5->setDiffuse(1, 1, 1, 1);
	candle5->setSpecular(1, 1, 1, 1);
	candle5->setAttenuation(1, 0, 0.1);
	_lightSources.push_back(candle5);

	LightSource* candle6 = new LightSource(6);
	candle6->setPosition(0, 15, 1, 1);
	candle6->setAmbient(0.7, 0.7, 0.7, 1);
	candle6->setDiffuse(1, 1, 1, 1);
	candle6->setSpecular(1, 1, 1, 1);
	candle6->setAttenuation(1.0, 0, 0.1);
	_lightSources.push_back(candle6);

	LightSource* spotlight = new LightSource(7);
	spotlight->setAmbient(0.8, 0.8, 0.8, 1);
	spotlight->setDiffuse(1, 1, 1, 1);
	spotlight->setSpecular(1, 1, 1, 1);
	spotlight->setExponent(new GLfloat(5));
	spotlight->setCutOff(new GLfloat(40));
	spotlight->setAttenuation(0, 0.6, 0.3);
	_lightSources.push_back(spotlight);

	initIsDone = true;
}