#pragma once
#include <string>
#include <map>
#include <utility>

//named gates

template<class CTYPE>
class NAMEDCLASS
{
private:
	std::string name;
	static std::map<std::string, CTYPE*> objRegister;
public:
	NAMEDCLASS() = delete;
	NAMEDCLASS(const std::string name, CTYPE* parent);
	virtual std::string getName() const;
	static std::pair<bool, CTYPE*> getObjWithName(std::string name);
};

template<class CTYPE>
std::map<std::string, CTYPE*> NAMEDCLASS<CTYPE>::objRegister;

template<class CTYPE>
NAMEDCLASS<CTYPE>::NAMEDCLASS(const std::string name, CTYPE* parent) :
	name(name)
{
	
	NAMEDCLASS<CTYPE>::objRegister.insert({ name, parent });
}

template<class CTYPE>
std::string NAMEDCLASS<CTYPE>::getName() const
{
	return this->name;
}

template<class CTYPE>
std::pair<bool,CTYPE*> NAMEDCLASS<CTYPE>::getObjWithName(std::string name)
{
	std::map<std::string, CTYPE*>::iterator res = NAMEDCLASS<CTYPE>::objRegister.find(name);

	if (res == NAMEDCLASS<CTYPE>::objRegister.end())
		return std::pair<bool, CTYPE*>(false, NULL);
	else
		return std::pair<bool, CTYPE*>(true, res->second);
}