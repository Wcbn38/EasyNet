#pragma once
#include <string>

//named gates

class NAMEDCLASS
{
private:
	std::string name;
public:
	NAMEDCLASS(const std::string name);
	virtual std::string getName();
};