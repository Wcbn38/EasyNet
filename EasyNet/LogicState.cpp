#include "LogicState.h"

//logic operators
LOGICSTATE operator+(LOGICSTATE o1, LOGICSTATE o2)
{
	ASSERT_LOGIC(o1, o2);

	if (o1 == L1 || o2 == L1)
		return L1;

	return L0;
}

LOGICSTATE operator*(LOGICSTATE o1, LOGICSTATE o2)
{
	ASSERT_LOGIC(o1, o2);

	if (o1 == L0 || o2 == L0)
		return L0;

	return L1;
}

LOGICSTATE operator^(LOGICSTATE o1, LOGICSTATE o2)
{
	ASSERT_LOGIC(o1, o2);

	if (o1 == L0)
	{
		return o2 == L0 ? L0 : L1;
	}
	else //o1 == L1
	{
		return o2 == L0 ? L1 : L0;
	}
}

LOGICSTATE operator!(LOGICSTATE o1)
{
	switch (o1)
	{
	case X: return X;
	case Z: return Z;
	case L0: return L1;
	case L1: return L0;
	default: return X;
	}
}

LOGICSTATE operator~(LOGICSTATE o1)
{
	switch (o1)
	{
	case X: return X;
	case Z: return Z;
	case L0: return L1;
	case L1: return L0;
	default: return X;
	}
}

//display operators
std::ostream& operator<<(std::ostream& stream, const LOGICSTATE state)
{
	switch (state)
	{
	case X:
		stream << "X";
		break;
	case Z:
		stream << "Z";
		break;
	case L0:
		stream << "0";
		break;
	case L1:
		stream << "1";
		break;
	default:
		stream << "UNKNOWN_STATE";
		break;
	}

	return stream;
}