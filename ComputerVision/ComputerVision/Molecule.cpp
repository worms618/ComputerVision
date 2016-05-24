#include "Molecule.h"
#include <sstream>

Molecule::Molecule()
{
	name = "Unknown";
}

Molecule::Molecule(const std::string & Name)
{
	name = Name;
}

Molecule::~Molecule()
{
}

void Molecule::addAtom(Atom * atom, int amount)
{
	atoms.push_back(std::pair<int, int>(atom->atomicNumber, amount));
}

std::string Molecule::toString(void)
{
	std::ostringstream oss;

	oss << "Molecule name: " << name;
	oss << "\nAtom: ";
	for (auto atom : atoms)
	{	
		oss << "[" << atom.first << "," << atom.second << "] ";
	}

	return oss.str();
}
