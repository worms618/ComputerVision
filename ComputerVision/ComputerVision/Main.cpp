#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "ScreenHandler.h"

#include <iostream>
#include "Atom.h"
#include "PeriodicTable.h"
#include "laboratory.h"

void display();
void idle();
bool justMoved = false;
void mousePassiveMotion(int x, int y);
void keyboard(unsigned char key, int, int);
void keyboardUp(unsigned char key, int, int);

ScreenHandler* screenHandler;

int main(int agrc, char* argv[])
{
	/*Atom oxygen(8,"oxygen","o",2,15.999);
	oxygen.setColor(1.0f, 0.0f, 0.0f, 1.0f);

	std::cout << oxygen.toString() << std::endl;
	
	PeriodicTable pTable;

	std::cout << pTable.getAtom(oxygen.atomicNumber)->toString() << std::endl;

	laboratory l;

	for (auto molecule : l.molecules)
		std::cout << molecule->toString() << std::endl;


	std::cin.get();*/

	screenHandler = new ScreenHandler();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(screenHandler->width, screenHandler->height);
	glutInit(&agrc, argv);
	glutCreateWindow("Eindopdracht Computervision Opengl");
	glutFullScreen();
	
	glEnable(GL_DEPTH_TEST);

	screenHandler->init();

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { screenHandler->width = w; screenHandler->height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(screenHandler->width / 2, screenHandler->height / 2);

	glutMainLoop();

	return 0;
}

void display()
{	
	screenHandler->draw();
}

void idle()
{	
	screenHandler->update();
}

void mousePassiveMotion(int x, int y)
{
	if (justMoved)
	{
		justMoved = false;
		return;
	}
	int dx = x - screenHandler->width / 2;
	int dy = y - screenHandler->height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		screenHandler->camera.rotY += dx / 10.0f;
		screenHandler->camera.rotX += dy / 10.0f;
		glutWarpPointer(screenHandler->width / 2, screenHandler->height / 2);
		justMoved = true;
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	screenHandler->keys[key] = true;
}

void keyboardUp(unsigned char key, int, int)
{
	screenHandler->keys[key] = false;
}
