#include <iostream>
#include "Atom.h"


int main(int agrc, char* argv[])
{
	Atom oxygen(8,"oxygen","o",2,15.999);
	oxygen.setColor(1.0f, 0.0f, 0.0f, 1.0f);

	std::cout << oxygen.getString() << std::endl;
	
	std::cin.get();

	return 0;
}