#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Atom.h"
#include "PeriodicTable.h"
#include "laboratory.h"

#define PERSPECTIVE 0
#define ORTHOGRAPHIC 1

int viewMode = PERSPECTIVE,width = 800,height = 600;
float lastFrameTime = 0;
const float speed = 10;

struct Camera
{
	float posX, posY, posZ, rotX, rotY;
} camera;

bool keys[255];

void display();
void idle();
void move(float angle, float fac, bool height);
bool justMoved = false;
void mousePassiveMotion(int x, int y);
void keyboard(unsigned char key, int, int);
void keyboardUp(unsigned char key, int, int);


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

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&agrc, argv);
	glutCreateWindow("Eindopdracht Computervision Opengl");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);

	glutMainLoop();

	return 0;
}

void display()
{
	glClearColor(135/256.0f, 206/256.0f, 235/256.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1f, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	glColor3f(0.1f, 1.0f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();

	glutSwapBuffers();
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	if (keys['a']) move(0, deltaTime*speed, false);
	if (keys['d']) move(180, deltaTime*speed, false);
	if (keys['w']) move(90, deltaTime*speed, false);
	if (keys['s']) move(270, deltaTime*speed, false);
	if (keys['q']) move(1, deltaTime*speed, true);
	if (keys['e']) move(-1, deltaTime*speed, true);

	glutPostRedisplay();
}

void move(float angle, float fac, bool height)
{
	if (height)
		camera.posY += angle*fac;
	else
	{
		camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
		camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
	}
}

void mousePassiveMotion(int x, int y)
{
	if (justMoved)
	{
		justMoved = false;
		return;
	}
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
		justMoved = true;
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}
