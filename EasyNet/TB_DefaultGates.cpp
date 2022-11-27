#include "DefaultGates.h"
#include <iostream>

void TB_DefaultGates()
{
	NAMEDNET<LOGICSTATE> i1Net(X, "\\NET_i1Net");
	NAMEDNET<LOGICSTATE> i2Net(X, "\\NET_i2Net");

	std::vector<NAMEDNET<LOGICSTATE>*> netArray = { &i1Net, &i2Net };

	AND and(netArray, "AND");
	NAND nand(netArray, "NAND");

	OR or(netArray, "OR");
	NOR nor(netArray, "NOR");

	XOR xor(netArray, "XOR");
	NXOR nxor(netArray, "NXOR");

	std::cout << "i1|i2| |AND|NAND|OR|NOR|XOR|NXOR|" << std::endl;

	i1Net.setNetState(L0); i2Net.setNetState(L0);

	std::cout << i1Net.getNetState() << " |" << i2Net.getNetState() << " | |";
	std::cout << and.getOutputNet(0)->getNetState() << "  |" << nand.getOutputNet(0)->getNetState() << "   |";
	std::cout << or.getOutputNet(0)->getNetState() << " |" << nor.getOutputNet(0)->getNetState() << "  |";
	std::cout << xor .getOutputNet(0)->getNetState() << "  |" << nxor.getOutputNet(0)->getNetState() << "   |";
	std::cout << std::endl;

	i1Net.setNetState(L0); i2Net.setNetState(L1);

	std::cout << i1Net.getNetState() << " |" << i2Net.getNetState() << " | |";
	std::cout << and .getOutputNet(0)->getNetState() << "  |" << nand.getOutputNet(0)->getNetState() << "   |";
	std::cout << or.getOutputNet(0)->getNetState() << " |" << nor.getOutputNet(0)->getNetState() << "  |";
	std::cout << xor .getOutputNet(0)->getNetState() << "  |" << nxor.getOutputNet(0)->getNetState() << "   |";
	std::cout << std::endl;

	i1Net.setNetState(L1); i2Net.setNetState(L0);

	std::cout << i1Net.getNetState() << " |" << i2Net.getNetState() << " | |";
	std::cout << and .getOutputNet(0)->getNetState() << "  |" << nand.getOutputNet(0)->getNetState() << "   |";
	std::cout << or.getOutputNet(0)->getNetState() << " |" << nor.getOutputNet(0)->getNetState() << "  |";
	std::cout << xor .getOutputNet(0)->getNetState() << "  |" << nxor.getOutputNet(0)->getNetState() << "   |";
	std::cout << std::endl;

	i1Net.setNetState(L1); i2Net.setNetState(L1);

	std::cout << i1Net.getNetState() << " |" << i2Net.getNetState() << " | |";
	std::cout << and .getOutputNet(0)->getNetState() << "  |" << nand.getOutputNet(0)->getNetState() << "   |";
	std::cout << or.getOutputNet(0)->getNetState() << " |" << nor.getOutputNet(0)->getNetState() << "  |";
	std::cout << xor .getOutputNet(0)->getNetState() << "  |" << nxor.getOutputNet(0)->getNetState() << "   |";
	std::cout << std::endl;
}