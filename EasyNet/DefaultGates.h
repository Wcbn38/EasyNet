#pragma once
#include "GenericGate.h"

#define CREATE_GENERIC(name, inNbPorts, outNbPorts)																						\
	class name : public GENERICGATE {																	\
	public:			name(std::vector<NAMEDNET<LOGICSTATE>*> inputs, std::string gateName) : GENERICGATE(inputs, inNbPorts, outNbPorts, gateName) {}				\
					void update(); };

CREATE_GENERIC(INV, 1, 1);
CREATE_GENERIC(AND, 2, 1);
CREATE_GENERIC(OR, 2, 1);
CREATE_GENERIC(NOR, 2, 1);
CREATE_GENERIC(NAND, 2, 1);
CREATE_GENERIC(XOR, 2, 1);
CREATE_GENERIC(NXOR, 2, 1);