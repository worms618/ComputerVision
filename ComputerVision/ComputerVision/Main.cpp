#include <iostream>
#include "Atom.h"
#include "PeriodicTable.h"
#include "laboratory.h"


int main(int agrc, char* argv[])
{
	Atom oxygen(8,"oxygen","o",2,15.999);
	oxygen.setColor(1.0f, 0.0f, 0.0f, 1.0f);

	std::cout << oxygen.toString() << std::endl;
	
	PeriodicTable pTable;

	std::cout << pTable.getAtom(oxygen.atomicNumber)->toString() << std::endl;

	laboratory l;

	for (auto molecule : l.molecules)
		std::cout << molecule->toString() << std::endl;


	std::cin.get();
	return 0;
}