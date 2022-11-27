#include "GenericGate.h"

GENERICGATE::GENERICGATE(std::vector<NAMEDNET<LOGICSTATE>*> inputs, int inSize, int outSize, std::string name) :
	NAMEDCLASS(name, this), inSize(inSize), outSize(outSize)
{
	for (int i = 0; i < outSize; i++)
		outputs.emplace_back(X, "\\NET_" + name + "_" + std::to_string(i));

	for (int i = 0; i < inSize; i++)
	{
		this->inputs.push_back(inputs[i]);
		this->inputs[i]->addConnectedGate(this);
	}
}

NAMEDNET<LOGICSTATE>* GENERICGATE::getOutputNet(int index)
{
	return &this->outputs[index];
}