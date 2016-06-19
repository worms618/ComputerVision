#define _USE_MATH_DEFINES
#include <cmath>
#include "Molecule.h"
#include <sstream>
#include <iostream>
#include <GL\freeglut.h>

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
	for (auto ab : atomBindings)
		delete ab;
}

void Molecule::addAtom(Atom * atom)
{
	//atoms.push_back(std::pair<int, int>(atom->atomicNumber, amount));
	atoms.push_back(atom->atomicNumber);
	bool containts = false;

	for (auto &atom_pair : atom_pairs)
	{
		if (atom_pair.first == atom->atomicNumber)
		{
			containts = true;
			break;
		}
	}
	if (!containts)
		atom_pairs.push_back(std::pair<int, int>(atom->atomicNumber, 0));

	for (auto &atom_pair : atom_pairs)
	{
		if (atom_pair.first == atom->atomicNumber)
		{
			++atom_pair.second;
		}
	}
}

void Molecule::updateAtomPairs()
{
	bool containts = false;
	for (auto &atom : atoms)
	{
		containts = false;
		for (auto &atom2 : atom_pairs)
		{
			if (atom2.first == atom)
			{
				containts = true;
				break;
			}
		}

		if (!containts)
			atom_pairs.push_back(std::pair<int, int>(atom, 0));
	}

	for (auto &atom : atoms)
	{
		for (auto &atom2 : atom_pairs)
		{
			if (atom2.first == atom)
			{
				++atom2.second;
			}
		}
	}
}

std::string Molecule::toString(void)
{
	std::ostringstream oss;
	
	oss << "Molecule name: " << name;
	oss << "\nAtom: ";
	oss << atomToString();

	return oss.str();
}

std::string Molecule::atomToString(void)
{
	std::ostringstream oss;
	for (auto atom : atom_pairs)
	{
		oss << "[" << atom.first << "," << atom.second << "] ";
	}

	return oss.str();
}

MoleculeInstance::MoleculeInstance(Molecule * m)
{
	molecule = m;
	for (auto atom : molecule->atoms)	
		atomInstances.push_back(new AtomInstance(atom));
	for (auto atomBinding : molecule->atomBindings)
		atomBindingInstances.push_back(new AtomBindingInstance(atomBinding));
	
	setAtoms();
	setAtomBindings();
	scale = 1.0f;	
}

MoleculeInstance::~MoleculeInstance()
{
	if (molecule)
		delete molecule;
	for (auto atom_instance : atomInstances)
		delete atom_instance;
	for (auto atom_binding : atomBindingInstances)
		delete atom_binding;
	
}

void MoleculeInstance::setAtoms()
{	
	for (auto ab : molecule->atomBindings)
	{		
		AtomInstance* baseAtom = atomInstances[ab->baseAtomIndex];
		AtomInstance* bindingAtom = atomInstances[ab->bindingAtomIndex];
		int bindings = ab->bindings;
		int distance = ab->distance;
		float angle = ab->angle;
		
		bindingAtom->position.x = baseAtom->position.x + (float)cos(angle / 180 * M_PI) * distance;
		if (angle < 0)
			bindingAtom->position.x *= -1;
		bindingAtom->position.y = baseAtom->position.y + (float)sin(angle / 180 * M_PI) * distance;
		if (angle > 0)
			bindingAtom->position.y *= -1;
	}
}

void MoleculeInstance::setAtomBindings()
{
	for (auto ab : atomBindingInstances)
	{
		ab->basePosition = atomInstances[ab->atomBinding->baseAtomIndex]->position;
		ab->bindingPosition = atomInstances[ab->atomBinding->bindingAtomIndex]->position;
	}
}