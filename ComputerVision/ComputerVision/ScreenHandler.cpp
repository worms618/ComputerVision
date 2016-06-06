#include "ScreenHandler.h"
#include <GL\freeglut.h>
#include "LaboratoryScreen.h"

ScreenHandler::ScreenHandler()
{
	memset(keys, 0, sizeof(keys));
}


ScreenHandler::~ScreenHandler()
{
	if (keys)
		delete keys;
	if (currentScreen)
		delete currentScreen;
}

void ScreenHandler::init()
{
	lastFrameTime = 0;
	
	width = 800;
	height = 600;

	mousePosition = Vec2f(width / 2, height / 2);

	currentScreen = new LaboratoryScreen();
	currentScreen->init();
}

void ScreenHandler::draw()
{
	glClearColor(135 / 256.0f, 206 / 256.0f, 235 / 256.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1f, 50);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	currentScreen->draw(width,height);

	glutSwapBuffers();
}

void ScreenHandler::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	currentScreen->camera.rotY += mouseOffSet.x / 10.0f;
	currentScreen->camera.rotX += mouseOffSet.y / 10.0f;
	if (currentScreen->camera.rotX > 90)
		currentScreen->camera.rotX = 90;
	if (currentScreen->camera.rotX < -90)
		currentScreen->camera.rotX = -90;


	if (keys['a']) currentScreen->moveCamera(0, deltaTime*speed, false);
	if (keys['d']) currentScreen->moveCamera(180, deltaTime*speed, false);
	if (keys['w']) currentScreen->moveCamera(90, deltaTime*speed, false);
	if (keys['s']) currentScreen->moveCamera(270, deltaTime*speed, false);
	if (keys['q']) currentScreen->moveCamera(1, deltaTime*speed, true);
	if (keys['e']) currentScreen->moveCamera(-1, deltaTime*speed, true);
	/*if (keys['o'])viewMode = ORTHOGRAPHIC;
	if (keys['p'])viewMode = PERSPECTIVE;*/

	currentScreen->update(deltaTime, keys);

	mousePosition = mousePosition + mouseOffSet;
	mouseOffSet = Vec2f(0, 0);

	glutPostRedisplay();
}

