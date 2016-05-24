#pragma once
#include <vector>
#include "PeriodicTable.h"
#include "Molecule.h"
class laboratory
{
public:
	laboratory();
	~laboratory();

	PeriodicTable* periodicTable;
	std::vector<Molecule*>molecules;

private:
	void load_molecules(void);
};

