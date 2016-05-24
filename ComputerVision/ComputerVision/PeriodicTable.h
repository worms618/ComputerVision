#pragma once
#include <vector>
#include "Atom.h"

class PeriodicTable
{
public:
	PeriodicTable();
	~PeriodicTable();
	Atom* getAtom(int atomicNumber);

private:
	void load_atoms(void);
	std::vector<Atom*>all_atoms;
};

