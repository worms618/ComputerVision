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
	//std::cout << molecules_data;
	file.close();

	for (auto molecule_data : molecules_data["molecules"])
	{
		std::string name = "Unknown";

		if (!molecule_data["molecule name"].isNull())
			name = molecule_data["molecule name"];

		Molecule * m = new Molecule(name);

		if (!molecule_data["atoms"].isNull())
		{
			for (auto atom_number : molecule_data["atoms"])
			{				
				m->addAtom(periodicTable->getAtom(atom_number));
			}
		}

		if (!molecule_data["molecule structuur"]["atom bindings"].isNull())
		{
			for (auto atom_binding : molecule_data["molecule structuur"]["atom bindings"])
			{
				Molecule::AtomBinding* ab = new Molecule::AtomBinding();

				if (!atom_binding["base atom index"].isNull())
					ab->baseAtomIndex = atom_binding["base atom index"];

				if (!atom_binding["binding atom index"].isNull())
					ab->bindingAtomIndex = atom_binding["binding atom index"];

				if (!atom_binding["bindings"].isNull())
					ab->bindings = atom_binding["bindings"];

				if (!atom_binding["angle"].isNull())
					ab->angle = atom_binding["angle"];

				if (!atom_binding["distance"].isNull())
					ab->distance = atom_binding["distance"];

				m->atomBindings.push_back(ab);
			}
		}

		molecules.push_back(m);
	}
}
