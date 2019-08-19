#include "MIPSSingleCycle.h"
#include <iostream>

int main() {
	MIPSSingleCycle Mips;


	Mips.Reset();

	// Testing

	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	Mips.EmulateCycle();
	std::cout << "r[1]: " << Mips.r[1] << "    r[30]: " << Mips.r[30] << std::endl;
	/*
	for (;;) {
		Mips.EmulateCycle();
		std::cout << Mips.r[30] << std::endl;
	}
	*/
	

 	return 0;
}