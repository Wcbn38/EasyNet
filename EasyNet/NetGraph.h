#pragma once
#include <vector>

//forward declarations
template <typename TSTATE> class NET;
template <typename TSTATE> class TGATE;

//definitions

template <typename TSTATE>
class TGATE
{
public:
	/**
	Get state of gate.
	\return state of gate
	*/
	virtual void update() = 0;

	/**
	Gets output net.
	\param index: output index.
	*/
	virtual NET<TSTATE>& getOutputNet(int index) = 0;
};

template <typename TSTATE>
class NET
{
private:
	std::vector<TGATE<TSTATE>*> connGates;
	TSTATE state;

public:
	NET(TSTATE defaultState);

	/**
	Sets the net state.
	\param state: state to set.
	*/
	virtual void setNetState(const TSTATE state);

	/**
	Gets the net state.
	\return net state.
	*/
	virtual TSTATE getNetState();

	/**
	Connects a gate to the net.
	\param gate: gate to connect.
	*/
	virtual void addConnectedGate(TGATE<TSTATE>* gate);
};

//implementation
template <typename TSTATE>
NET<TSTATE>::NET(TSTATE defaultState)
{
	this->state = defaultState;
}


template <typename TSTATE>
void NET<TSTATE>::setNetState(const TSTATE state)
{
	this->state = state;
	
	std::vector<TGATE<TSTATE>*>::iterator it;
	for (it = this->connGates.begin(); it != this->connGates.end(); it++)
	{
		(*it)->update();
	}
}

template <typename TSTATE>
TSTATE NET<TSTATE>::getNetState()
{
	return this->state;
}

template <typename TSTATE>
void NET<TSTATE>::addConnectedGate(TGATE<TSTATE>* gate)
{
	this->connGates.push_back(gate);
}