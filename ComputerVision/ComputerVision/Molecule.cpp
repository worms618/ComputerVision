#define _USE_MATH_DEFINES
#include <cmath>
#include "Molecule.h"
#include <sstream>
#include <iostream>


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
}

std::string Molecule::toString(void)
{
	std::ostringstream oss;
	std::vector<std::pair<int, int>>atom_pairs;

	for (auto atom : atoms)
	{
		for (auto atom2 : atom_pairs)
		{
			if (atom2.first == atom)
			{
				atom2.second++;
				break;
			}
			else
				atom_pairs.push_back(std::pair<int, int>(atom, 1));
		}
	}

	oss << "Molecule name: " << name;
	oss << "\nAtom: ";
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

//http://www.thjsmith.com/40/cylinder-between-two-points-opengl-c
void MoleculeInstance::setAtomBindings()
{
	for (auto ab : atomBindingInstances)
	{
		ab->basePosition = atomInstances[ab->atomBinding->baseAtomIndex]->position;
		ab->bindingPosition = atomInstances[ab->atomBinding->bindingAtomIndex]->position;
	}
}

