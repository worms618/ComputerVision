#pragma once
#include <string>
#include "Vector.h"

class Atom
{
public:
	Atom();
	Atom(int, std::string, std::string, int, float);
	~Atom();


	std::string chemicalSymbol;
	std::string elementName;
	int atomicNumber, covalently;
	float atomicMass;

	struct Color_RGBA
	{
		float red, green, blue, alfa;
	}color;

	void setColor(float r, float g, float b, float a);
	std::string toString(void);
};

class AtomInstance
{
public:
	AtomInstance(int an);
	~AtomInstance();

	int atomicNumber;
	Vec3f position, rotation;
	float scale;
};



