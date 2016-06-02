#pragma once
#include "atom.h"
#include <vector>
#include "Vector.h"

class Molecule
{
public:
	Molecule();
	Molecule(const std::string &);
	~Molecule();
	void addAtom(Atom*);
	std::string toString(void);

	class AtomBinding
	{
	public:
		AtomBinding();
		~AtomBinding();

		int baseAtomIndex, bindingAtomIndex, bindings, distance;
		float angle;
	};

	std::vector<AtomBinding*> atomBindings;
	std::vector<int>atoms;
private:
	std::string name;
	//std::vector<std::pair<int, int>>atoms;	
	
};

class MoleculeInstance
{
public:
	MoleculeInstance(Molecule *);
	~MoleculeInstance();

	Molecule* molecule;

	Vec3f rotation, position;
	float scale;
	std::vector<AtomInstance*>atomInstances;
private:
	void setAtoms();
};



