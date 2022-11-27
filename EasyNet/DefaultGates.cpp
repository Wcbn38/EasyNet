#include "DefaultGates.h"

void INV::update()
{
	outputs[0].setNetState(!inputs[0]->getNetState());
}

void AND::update()
{
	outputs[0].setNetState(inputs[0]->getNetState() * inputs[1]->getNetState());
}

void OR::update()
{
	outputs[0].setNetState(inputs[0]->getNetState() + inputs[1]->getNetState());
}

void NOR::update()
{
	outputs[0].setNetState(!(inputs[0]->getNetState() + inputs[1]->getNetState()));
}

void NAND::update()
{
	outputs[0].setNetState(!(inputs[0]->getNetState() * inputs[1]->getNetState()));
}

void XOR::update()
{
	outputs[0].setNetState(inputs[0]->getNetState() ^ inputs[1]->getNetState());
}

void NXOR::update()
{
	outputs[0].setNetState(!(inputs[0]->getNetState() ^ inputs[1]->getNetState()));
}