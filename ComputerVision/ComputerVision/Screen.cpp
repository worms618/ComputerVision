#include "Screen.h"
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>

Screen::Screen()
{
}


Screen::~Screen()
{
}

void Screen::init()
{
	camera.posX = 0;
	camera.posY = 0;
	camera.posZ = 0;
	camera.rotX = 0;
	camera.rotY = 0;	
}

void Screen::draw(int width,int height)
{	
	
}

void Screen::update(float deltaTime)
{
}

void Screen::moveCamera(float angle, float fac, bool height)
{
	if (height)
		camera.posY += angle*fac;
	else
	{
		camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
		camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
	}
}
