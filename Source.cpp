#include "GameManager.h"
#include <GL/glut.h>
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h>

GameManager* MicroMachines = new GameManager();

void timer(int t) {
	MicroMachines->onTimer();
	glutTimerFunc(20, timer, 1);
}

void orangeSpeedTimer(int t) {
	MicroMachines->raiseOrangeSpeed();
	glutTimerFunc(8000, orangeSpeedTimer, 1);
}

void reAlive(int i) {
	MicroMachines->resetOrange(i);
}

void display() {
	MicroMachines->display();
}

void reshape(int w, int h) {
	MicroMachines->reshape(w, h);
}

void keyPressed(int key, int x, int y) {
	MicroMachines->keyPressed(key, x, y);
}

void keyAPressed(unsigned char key, int x, int y) {
	MicroMachines->keyAPressed(key, x, y);
}

void keysReleased(int key, int x, int y) {
	MicroMachines->keyReleased(key, x, y);
}

void initGame() {
	delete MicroMachines;
	MicroMachines = new GameManager();
	MicroMachines->init();
}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	MicroMachines->init();
	//  Requisita uma janela com buffer duplo e true color com um Z-buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(800, 50);
	glutCreateWindow("Micro Machines");
	//  Habilita o teste de profundidade do Z-buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//  Passa o controle dos eventos para o GLUT
	glutSpecialFunc(keyPressed);
	glutKeyboardFunc(keyAPressed);
	glutSpecialUpFunc(keysReleased);
	glutTimerFunc(20, timer, 0);
	glutTimerFunc(8000, orangeSpeedTimer, 1);
	glutMainLoop();

	return 0;

}