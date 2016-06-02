#pragma once
#include "Screen.h"
#include "Vector.h"

class ScreenHandler
{
public:
	ScreenHandler();
	~ScreenHandler();

	void init();
	void draw();
	void update();

	int width, height;

	const float speed = 10;
	float lastFrameTime;

	bool keys[255];

	Screen* currentScreen;

	Vec2f mousePosition;
	Vec2f mouseOffSet;
};

