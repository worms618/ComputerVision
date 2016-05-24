#include "laboratory.h"
#include "json.h"
#include <fstream>
#include <iostream>


laboratory::laboratory()
{
	periodicTable = new PeriodicTable();
	load_molecules();
}


laboratory::~laboratory()
{
	if (periodicTable)
		delete periodicTable;
}

void laboratory::load_molecules(void)
{
	std::ifstream file("Molecules_Data.json");
	if (!file.is_open())
	{
		std::cout << "Can't open molecules_data file\n" << std::endl;
		return;
	}
	json::Value molecules_data = json::readJson(file);
	std::cout << molecules_data;
	file.close();

	for (auto molecule_data : molecules_data["molecules"])
	{
		std::string name = "Unknown";

		if (!molecule_data["molecul name"].isNull())
			name = molecule_data["molecul name"];

		Molecule * m = new Molecule(name);

		if (!molecule_data["atoms"].isNull())
		{
			for (auto atom_data : molecule_data["atoms"])
			{
				int an = -1, aoa = -1;
				
				if (!atom_data["atomic number"].isNull())
					an = atom_data["atomic number"];
				if (!atom_data["amount of atoms"].isNull())
					aoa = atom_data["amount of atoms"];

				m->addAtom(periodicTable->getAtom(an), aoa);
			}
		}
		molecules.push_back(m);
	}
}
