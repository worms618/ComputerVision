#pragma once
#define PERSPECTIVE 0
#define ORTHOGRAPHIC 1

class ScreenHandler
{
public:
	ScreenHandler();
	~ScreenHandler();

	void init();
	void draw();
	void update();
	void moveCamera(float angle, float fac, bool height);

	int width, height;

	const float speed = 10;
	float lastFrameTime;

	int viewMode;

	struct Camera
	{
		float posX, posY, posZ, rotX, rotY;
	} camera;

	bool keys[255];

};

