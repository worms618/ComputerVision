#pragma once
#include <string>
#include "Vector.h"
#include <vector>

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

	void bindColor(void);
};

class AtomInstance
{
public:
	AtomInstance();
	AtomInstance(int an);
	~AtomInstance();

	int atomicNumber;
	Vec3f position, rotation;
	float scale;
};


class AtomBinding
{
public:
	AtomBinding();
	~AtomBinding();

	int baseAtomIndex, bindingAtomIndex, bindings, distance;
	float angle;
};

class AtomBindingInstance
{
public:
	AtomBindingInstance(AtomBinding*);
	~AtomBindingInstance();

	AtomBinding* atomBinding;

	//Vec3f basePosition, bindingPosition;
	std::vector<std::pair<Vec3f, Vec3f>>positions;
	float scale,radius;	
};





