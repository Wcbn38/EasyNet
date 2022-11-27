#include "NamedClass.h"

NAMEDCLASS::NAMEDCLASS(const std::string name) :
	name(name)
{

}

std::string NAMEDCLASS::getName()
{
	return this->name;
}