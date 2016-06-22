#pragma once
#include <string>


class MoleculeInfoPanel
{
public:
	MoleculeInfoPanel();
	~MoleculeInfoPanel();
	
	void draw(int width, int height);
	void updateInfoPanel(std::string,std::string,int);
private:
	std::string name;
	std::string molecularFormula;
	std::string atomicMass;

	void drawString(std::string str, int x, int y);
};