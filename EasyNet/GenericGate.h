#pragma once
#include "LogicState.h"
#include "NamedClass.h"
#include "NetGraph.h"

//generic gate
template<int PORTIN, int PORTOUT>
class GENERICGATE : public TGATE<LOGICSTATE>
{
protected:
	NET<LOGICSTATE>* inputs[PORTIN];
	NET<LOGICSTATE> outs[PORTOUT] = {X};

public:
	GENERICGATE() = delete;

	/**
	Generic gates constructor.
	\param inputs: logic gates to connect to.
	*/
	GENERICGATE(NET<LOGICSTATE>* inputs[PORTIN]);

	/**
	Get specific output net.
	\param index: index of the net.
	\return output net.
	*/
	NET<LOGICSTATE>* getOutputNet(int index);

	/**
	Gets the number of output nets.
	\return number of output nets.
	*/
	inline int getOutNetNb() { return PORTOUT; }

	/**
	Gets the number of input nets.
	\return number of input nets.
	*/
	inline int getInNetNb() { return PORTIN; }
};

template<int PORTIN, int PORTOUT>
GENERICGATE<PORTIN, PORTOUT>::GENERICGATE(NET<LOGICSTATE>* inputs[PORTIN])
{
	for (int i = 0; i < PORTIN; i++)
	{
		inputs[i]->addConnectedGate(this);
		this->inputs[i] = inputs[i];
	}
}

template<int PORTIN, int PORTOUT>
NET<LOGICSTATE>* GENERICGATE<PORTIN, PORTOUT>::getOutputNet(int index)
{
	return &this->outs[index];
}	