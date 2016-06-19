#pragma once
#include "Screen.h"
#include "Vector.h"

struct KeyboardState
{
	bool keys[255];
};

class ScreenHandler
{
public:
	ScreenHandler();
	~ScreenHandler();

	void init();
	void draw();
	void update();
	void checkKeysPressed();

	int width, height;

	const float speed = 10;
	float lastFrameTime;

	bool keysPressed[255];

	KeyboardState state;
	KeyboardState prev;
	
	Screen* currentScreen;

	Vec2f mousePosition;
	Vec2f mouseOffSet;
};

