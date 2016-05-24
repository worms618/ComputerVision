#pragma once
#include <string>

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



