#pragma once
#include "LogicState.h"
#include <list>
#include <string>
#include "NamedNetGraph.h"

template <typename TSTATE>
struct STIMULI
{
	NAMEDNET<TSTATE>* net = NULL;
	LOGICSTATE newState = X;
};