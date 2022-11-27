#pragma once
#include "GenericGate.h"

#define CREATE_GENERIC(name, inNbPorts, outNbPort)																						\
	class name : public GENERICGATE<inNbPorts, outNbPort>, public NAMEDCLASS {																	\
	public:			name(NET<LOGICSTATE>* inputs[inNbPorts], std::string name) : GENERICGATE(inputs), NAMEDCLASS(name) {}				\
					void update(); };

CREATE_GENERIC(INV, 1, 1);
CREATE_GENERIC(AND, 2, 1);
CREATE_GENERIC(OR, 2, 1);
CREATE_GENERIC(NOR, 2, 1);
CREATE_GENERIC(NAND, 2, 1);
CREATE_GENERIC(XOR, 2, 1);
CREATE_GENERIC(NXOR, 2, 1);