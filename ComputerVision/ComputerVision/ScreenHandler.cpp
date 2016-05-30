#include "ScreenHandler.h"
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>



ScreenHandler::ScreenHandler()
{
	memset(keys, 0, sizeof(keys));
}


ScreenHandler::~ScreenHandler()
{
	if (keys)
		delete keys;
}

void ScreenHandler::init()
{
	lastFrameTime = 0;
	viewMode = PERSPECTIVE;
	camera.posX = 0;
	camera.posY = 0;
	camera.posZ = 0;
	camera.rotX = 0;
	camera.rotY = 0;
	width = 800;
	height = 600;
}

void ScreenHandler::draw()
{
	glClearColor(135 / 256.0f, 206 / 256.0f, 235 / 256.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (viewMode)
	{
	case PERSPECTIVE:
		gluPerspective(60.0f, (float)width / height, 0.1f, 50);
		break;
	case ORTHOGRAPHIC:
		glOrtho(-5, 5, -5, 5, 0.1f, 50);
		break;
	default:
		exit(0);
		break;
	}

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

void ScreenHandler::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	if (camera.rotX > 90)
		camera.rotX = 90;
	if (camera.rotX < -90)
		camera.rotX = -90;


	if (keys['a']) moveCamera(0, deltaTime*speed, false);
	if (keys['d']) moveCamera(180, deltaTime*speed, false);
	if (keys['w']) moveCamera(90, deltaTime*speed, false);
	if (keys['s']) moveCamera(270, deltaTime*speed, false);
	if (keys['q']) moveCamera(1, deltaTime*speed, true);
	if (keys['e']) moveCamera(-1, deltaTime*speed, true);
	if (keys['o'])viewMode = ORTHOGRAPHIC;
	if (keys['p'])viewMode = PERSPECTIVE;

	glutPostRedisplay();
}

void ScreenHandler::moveCamera(float angle, float fac, bool height)
{
	if (height)
		camera.posY += angle*fac;
	else
	{
		camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
		camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
	}
}
