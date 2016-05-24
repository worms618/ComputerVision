#include "PeriodicTable.h"
#include <fstream>
#include <iostream>
#include "Atom.h"
#include "json.h"


PeriodicTable::PeriodicTable()
{
	load_atoms();
}


PeriodicTable::~PeriodicTable()
{
}

Atom * PeriodicTable::getAtom(int atomicNumber)
{
	for (auto &atom : all_atoms)
	{
		if (atom->atomicNumber == atomicNumber)
			return atom;
	}
	return nullptr;
}

void PeriodicTable::load_atoms()
{
	std::ifstream file("Atoms_Data.json");
	if (!file.is_open())
	{
		std::cout << "Can't open atoms and molecul file\n" << std::endl;
		return;
	}
	json::Value atoms_data = json::readJson(file);
	std::cout << atoms_data;
	file.close();

	for (auto atom_data : atoms_data["atoms"])
	{
		//setting default values for the atom		
		int an = -1, c = -1;
		float am = -1.0f;
		std::string en = "Unknown", cs = "Unknown";
		float rgba[4];
		for (int i = 0; i < 3; i++)
			rgba[i] = -1.0f;
		rgba[3] = 1.0f;

		if (!atom_data["atomic number"].isNull())
			an = atom_data["atomic number"];

		if (!atom_data["element name"].isNull())
			en = atom_data["element name"];

		if (!atom_data["chemical symbol"].isNull())
			cs = atom_data["chemical symbol"];

		if (!atom_data["covalently"].isNull())
			c = atom_data["covalently"];

		if (!atom_data["atomic mass"].isNull())
			am = atom_data["atomic mass"].asFloat();

		if (!atom_data["visualization"].isNull())
			for (int i = 0; i < 4; i++)
				rgba[i] = atom_data["visualization"][i].asFloat();

		Atom* atom = new Atom(an, en, cs, c, am);
		atom->setColor(rgba[0], rgba[1], rgba[2], rgba[3]);
		all_atoms.push_back(atom);
	}
}

