#pragma once
#include "LogicState.h"
#include "NamedClass.h"
#include "NamedNetGraph.h"
#include <vector>

//generic gate
class GENERICGATE : public TGATE<LOGICSTATE>, public NAMEDCLASS<GENERICGATE>
{
protected:
	std::vector<NAMEDNET<LOGICSTATE>*> inputs;
	std::vector<NAMEDNET<LOGICSTATE>> outputs;
	int inSize, outSize;

public:
	/**
	Generic gates constructor.
	*/
	GENERICGATE() = delete;

	/**
	Generic gates constructor.
	\param inputs: logic gates to connect to.
	*/
	GENERICGATE(std::vector<NAMEDNET<LOGICSTATE>*> inputs, int inSize, int outSize, std::string name);

	/**
	Get specific output net.
	\param index: index of the net.
	\return output net.
	*/
	NAMEDNET<LOGICSTATE>* getOutputNet(int index);

	/**
	Gets the number of output nets.
	\return number of output nets.
	*/
	inline int getOutNetNb() { return outSize; }

	/**
	Gets the number of input nets.
	\return number of input nets.
	*/
	inline int getInNetNb() { return inSize; }
};