#include "Atom.h"

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
