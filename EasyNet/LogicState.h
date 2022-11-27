#pragma once
#include <ostream>

#define ASSERT_LOGIC(a, b)			\
	if (a == X || b == X)			\
		return X;					\
	else if (a == Z || b == Z)	\
		return Z; 

enum LOGICSTATE
{
	L0,
	L1,
	X,
	Z
};

//logic operators
LOGICSTATE operator+(LOGICSTATE o1, LOGICSTATE o2);
LOGICSTATE operator*(LOGICSTATE o1, LOGICSTATE o2);
LOGICSTATE operator^(LOGICSTATE o1, LOGICSTATE o2);
LOGICSTATE operator!(LOGICSTATE o1);
LOGICSTATE operator~(LOGICSTATE o1);

//removed operators
LOGICSTATE operator++(LOGICSTATE& o1, int i) = delete;
LOGICSTATE operator--(LOGICSTATE& o1, int i) = delete;

//display operators
std::ostream& operator<<(std::ostream& stream, const LOGICSTATE state);