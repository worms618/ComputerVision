#define _USE_MATH_DEFINES
#include <cmath>
#include "Molecule.h"
#include <sstream>
#include <iostream>
#include <GL\freeglut.h>
#include "Matrix.h"

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
		float angle = ab->angle,s,c;
		angle = angle / 180 * M_PI;
		
		bindingAtom->position = bindingAtom->position - baseAtom->position;

		bindingAtom->position.x += (float)cos(angle) * distance;
		bindingAtom->position.y += (float)sin(angle) * distance;
		
		bindingAtom->position = bindingAtom->position + baseAtom->position;

		if (angle < 0)
			bindingAtom->position.x *= -1;
		if (angle > 0)
			bindingAtom->position.y *= -1;		
	}
}

void MoleculeInstance::setAtomBindings()
{
	float offset = 0.4f;
	//http://math.stackexchange.com/questions/41298/reflecting-a-point-over-a-line-created-by-two-other-points
	for (auto ab : atomBindingInstances)
	{		
		Vec3f base = atomInstances[ab->atomBinding->baseAtomIndex]->position;
		Vec3f binding = atomInstances[ab->atomBinding->bindingAtomIndex]->position;

		if (ab->atomBinding->bindings == 1)
		{			
			ab->positions.push_back(std::pair<Vec3f, Vec3f>(base, binding));
		}
		else if (ab->atomBinding->bindings == 2)
		{			
			//find 1 parralell line with base-line
			Vec3f base1, binding1;
			float dx, dy;
			dx = binding.x - base.x;
			dy = binding.y - base.y;

			Vec3f dif(dy, -dx,0);
			dif.Normalize();

			dif = dif * offset / 2;
			base1 = base + dif;
			binding1 = binding + dif;

			ab->positions.push_back(std::pair<Vec3f, Vec3f>(base, binding));
			ab->positions.push_back(std::pair<Vec3f, Vec3f>(base1, binding1));			
		}
	}
}