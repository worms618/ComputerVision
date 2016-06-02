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
	void update(float deltaTime);
	laboratory* lab;
private:
	void drawMolecule(const MoleculeInstance * m);
	void drawAtom(AtomInstance * a);
	void drawAtomBinding(AtomBindingInstance * ab);
	

	std::vector<MoleculeInstance*>molecule_instances;

	Model* atomModel;
};

