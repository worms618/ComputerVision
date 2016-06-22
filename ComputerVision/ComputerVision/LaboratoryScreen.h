#pragma once
#include "Screen.h"
#include "laboratory.h"
#include "Model.h"
#include <vector>
#include <string>
#include "MoleculeInfoPanel.h"
#include "Skybox.h"

class LaboratoryScreen : public Screen
{
public:
	LaboratoryScreen();
	~LaboratoryScreen();

	void init();
	void draw(int, int);
	void update(float deltaTime, bool keys[]);
	//void update(float deltaTime, bool keys[], bool prevKeys[]);
	laboratory* lab;
private:
	void drawMolecule(MoleculeInstance * m);
	void drawAtom(AtomInstance * a);
	void drawAtomBinding(AtomBindingInstance* abi);
	
	void updateMoleculeData();

	int index;
	std::vector<MoleculeInstance*>molecule_instances;
	MoleculeInstance* currentMolecule;
	Model* atomModel;
	MoleculeInfoPanel mip;

	Skybox* skybox;
};

