#pragma once
#include "atom.h"
#include <vector>

class Molecule
{
public:
	Molecule();
	Molecule(const std::string &);
	~Molecule();
	void addAtom(Atom*, int);
	std::string toString(void);
private:
	std::string name;
	std::vector<std::pair<int, int>>atoms;
};

