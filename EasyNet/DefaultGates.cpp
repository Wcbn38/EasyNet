#include "DefaultGates.h"

void INV::update()
{
	outs[0].setNetState(!inputs[0]->getNetState());
}

void AND::update()
{
	outs[0].setNetState(inputs[0]->getNetState() * inputs[1]->getNetState());
}

void OR::update()
{
	outs[0].setNetState(inputs[0]->getNetState() + inputs[1]->getNetState());
}

void NOR::update()
{
	outs[0].setNetState(!(inputs[0]->getNetState() + inputs[1]->getNetState()));
}

void NAND::update()
{
	outs[0].setNetState(!(inputs[0]->getNetState() * inputs[1]->getNetState()));
}

void XOR::update()
{
	outs[0].setNetState(inputs[0]->getNetState() ^ inputs[1]->getNetState());
}

void NXOR::update()
{
	outs[0].setNetState(!(inputs[0]->getNetState() ^ inputs[1]->getNetState()));
}