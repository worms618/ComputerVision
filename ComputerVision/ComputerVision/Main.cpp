#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "ScreenHandler.h"

#include <iostream>
#include "Atom.h"
#include "PeriodicTable.h"
#include "laboratory.h"
#include "Matrix.h"

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

	//Matrix::reflect2D(Vec2f(4, 5), 180);
	//Matrix::rotate3D(Vec3f(5, 5, 0), 90);
	/*Matrix m1 = Matrix::identity();
	Matrix m2 = Matrix::identity();
	int count = 0;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			m2.data[r][c] = count;
			count++;
		}
	}
	
	Matrix m3 = (m1 * m2);
	m3 = m2 * m3;
	m3 = m1 * m3;*/

	screenHandler = new ScreenHandler();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(screenHandler->width, screenHandler->height);
	glutInit(&agrc, argv);
	glutCreateWindow("Eindopdracht Computervision Opengl");
	glutFullScreen();	
	
	GLfloat light_positionlt[] = {250,ScreenHandler::perpective/2,250,1.0 };
	GLfloat light_positionrt[] = { 750,ScreenHandler::perpective / 2,250,1.0 };
	GLfloat light_positionld[] = { 250,ScreenHandler::perpective / 2,750,1.0 };
	GLfloat light_positionrd[] = { 750,ScreenHandler::perpective / 2,750,1.0 };
	GLfloat lightColor[] = { 1.0f,1.0f,1.0f,1.0f };
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_positionlt);
	glLightfv(GL_LIGHT1, GL_POSITION, light_positionrt);
	glLightfv(GL_LIGHT2, GL_POSITION, light_positionld);
	glLightfv(GL_LIGHT3, GL_POSITION, light_positionrd);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glEnable(GL_DEPTH_TEST);

	screenHandler->init();

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { screenHandler->width = w; screenHandler->height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(screenHandler->width / 2, screenHandler->height / 2);

	glutSetCursor(GLUT_CURSOR_NONE);

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
		screenHandler->mouseOffSet = screenHandler->mouseOffSet + Vec2f(dx, dy);
		glutWarpPointer(screenHandler->width / 2, screenHandler->height / 2);
		justMoved = true;
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	//screenHandler->keys[key] = true;
	screenHandler->state.keys[key] = true;
}

void keyboardUp(unsigned char key, int, int)
{
	//screenHandler->keys[key] = false;
	screenHandler->state.keys[key] = false;
}
