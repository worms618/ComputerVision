#include "ScreenHandler.h"
#include <GL\freeglut.h>
#include "LaboratoryScreen.h"

ScreenHandler::ScreenHandler()
{
	memset(keysPressed, 0, sizeof(keysPressed));
	memset(state.keys, 0, sizeof(state.keys));
	memset(prev.keys, 0, sizeof(prev.keys));
}


ScreenHandler::~ScreenHandler()
{	
	if (keysPressed)
		delete keysPressed;
	if (state.keys)
		delete[] state.keys;
	if (prev.keys)
		delete[] prev.keys;
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


	if (state.keys['a']) currentScreen->moveCamera(0, deltaTime*speed, false);
	if (state.keys['d']) currentScreen->moveCamera(180, deltaTime*speed, false);
	if (state.keys['w']) currentScreen->moveCamera(90, deltaTime*speed, false);
	if (state.keys['s']) currentScreen->moveCamera(270, deltaTime*speed, false);
	if (state.keys['q']) currentScreen->moveCamera(1, deltaTime*speed, true);
	if (state.keys['e']) currentScreen->moveCamera(-1, deltaTime*speed, true);
	/*if (keys['o'])viewMode = ORTHOGRAPHIC;
	if (keys['p'])viewMode = PERSPECTIVE;*/
	
	checkKeysPressed();
	currentScreen->update(deltaTime, keysPressed);	
	//currentScreen->update(deltaTime, state.keys, prev.keys);

	mousePosition = mousePosition + mouseOffSet;
	mouseOffSet = Vec2f(0, 0);
	prev = state;
	glutPostRedisplay();
}

void ScreenHandler::checkKeysPressed()
{
	for (int i = 0; i < 256; i++)
	{
		if (state.keys[i] != prev.keys[i])
		{
			if (!state.keys[i])
			{
				keysPressed[i] = true;
			}
		}
		else
			keysPressed[i] = false;
	}
}
