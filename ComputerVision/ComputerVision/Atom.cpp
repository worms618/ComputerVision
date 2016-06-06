#include "Atom.h"
#include <GL\freeglut.h>
#include <sstream>

Atom::Atom()
{
	atomicNumber = -1;
	elementName = "Unkown";
	chemicalSymbol = "Unknown";
	covalently = -1;
	atomicMass = -1;
	setColor(-1.0f, -1.0f, -1.0f, 1.0f);
}

Atom::Atom(int AtomicNumber, std::string elementName,
	std::string chemicalSymbol, int covalently,
	float AtomicMass)
{
	this->atomicNumber = AtomicNumber;
	this->elementName = elementName;
	this->chemicalSymbol = chemicalSymbol;
	this->covalently = covalently;
	this->atomicMass = AtomicMass;
}


Atom::~Atom()
{
}

void Atom::setColor(float r, float g, float b, float a)
{
	color.red = r;
	color.green = g;
	color.blue = b;
	color.alfa = a;
}

std::string Atom::toString(void)
{
	std::ostringstream oss;

	oss << "Atomic number: " << atomicNumber;
	oss << "\nElement name: "<< elementName;
	oss << "\nChemical symbol: " << chemicalSymbol;
	oss << "\nCovalently: " << covalently;
	oss << "\nAtomic mass: " << atomicMass;	

	return oss.str();
}

void Atom::bindColor(void)
{
	glColor4f(color.red,
		color.green,
		color.blue,
		color.alfa);
}

AtomInstance::AtomInstance()
{
	for (int i = 0; i < 3; i++)
	{
		position[i] = 0;
		rotation[i] = 0;
	}
	scale = 1.0f;
}

AtomInstance::AtomInstance(int an)
{
	atomicNumber = an;
	for (int i = 0; i < 3; i++)
	{
		position[i] = 0;
		rotation[i] = 0;
	}
	scale = 1.0f;
}

AtomInstance::~AtomInstance()
{
	
}

AtomBinding::AtomBinding()
{
	baseAtomIndex = -1;
	bindingAtomIndex = -1;
	bindings = -1;
	distance = -1;
}


AtomBinding::~AtomBinding()
{
}



AtomBindingInstance::AtomBindingInstance(AtomBinding* ab)
{
	atomBinding = ab;
	scale = 1.0f;	
	radius = 0.5f;	
}


AtomBindingInstance::~AtomBindingInstance()
{
	if (atomBinding)
		delete atomBinding;	
}
