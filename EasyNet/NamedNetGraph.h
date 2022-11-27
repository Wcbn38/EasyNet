#pragma once
#include "NamedClass.h"
#include "NetGraph.h"

template <typename TSTATE>
class NAMEDNET : public NET<TSTATE>, public NAMEDCLASS<NAMEDNET<TSTATE>>
{
public:
	NAMEDNET(TSTATE defaultState, std::string name) :
		NET<TSTATE>(defaultState), NAMEDCLASS<NAMEDNET>(name, this)
	{}
};