#pragma once
#include "Screen.h"
#include "laboratory.h"
#include "Model.h"
#include <vector>

class LaboratoryScreen : public Screen
{
public:
	LaboratoryScreen();
	~LaboratoryScreen();

	void init();
	void draw(int, int);
	void update(float deltaTime, bool keys[]);
	laboratory* lab;
private:
	void drawMolecule(MoleculeInstance * m);
	void drawAtom(AtomInstance * a);
	void drawAtomBinding(AtomBindingInstance* abi);
		
	int index;
	std::vector<MoleculeInstance*>molecule_instances;
	MoleculeInstance* currentMolecule;
	Model* atomModel;
};

