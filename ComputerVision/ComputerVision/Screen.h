#pragma once

class Screen
{
public:
	Screen();
	~Screen();

	virtual void init();
	virtual void draw(int,int);
	virtual void update(float deltaTime);

	struct Camera
	{
		float posX, posY, posZ, rotX, rotY;
	} camera;

	void moveCamera(float angle, float fac, bool height);
};

