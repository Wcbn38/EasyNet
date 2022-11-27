#pragma once
#include <fstream>
#include <string>
#include <list>
#include <set>

#define LEX_SUCCESS 0x00

//file errors
#define LEX_FILE_NOT_OPENED 0x10

struct DELIM
{
	std::string tag;
	bool discard;
};

struct DELIM_CMP
{
	using is_transparent = void;

	bool operator() (DELIM const& o1, DELIM const& o2) const;
	bool operator() (DELIM const& del, const std::string str) const;
	bool operator() (const std::string str, DELIM const& del) const;
};

//delim creator
#define DELIM_TYPE std::set<DELIM, DELIM_CMP>

/**
Standard lexer, not working with wide character set.
\param file: file to lex.
\param delims: seperators.
\param lexedList: list to complete with extracted words.
\return LEX_SUCCESS (0) on success.
*/
int lex(std::fstream& file, DELIM_TYPE & delims, std::list<std::string>& lexedList);
