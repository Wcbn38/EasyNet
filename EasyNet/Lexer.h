#pragma once
#include <fstream>
#include <string>
#include <list>
#include <map>

//error ranges from 0x000 to 0x100
#define LEX_ERROR_OFFSET 0x000

//error codes
#define LEX_SUCCESS LEX_ERROR_OFFSET + 0x00
#define LEX_FILE_NOT_OPENED LEX_ERROR_OFFSET + 0x010

struct DELIM
{
	std::string tag;
	bool discard;
};


struct DELIM_CMP
{
	bool operator()(std::string const& str1, std::string const& str2) const
	{
		return str1.back() > str2.back();
	}
};

//delim creator
#define DELIM_TYPE std::map<std::string, bool, DELIM_CMP>

/**
Standard lexer, not working with wide character set.
\param file: file to lex.
\param delims: seperators.
\param lexedList: list to complete with extracted words.
\return LEX_SUCCESS (0) on success.
*/
int lex(std::fstream& file, DELIM_TYPE & delims, std::list<std::string>& lexedList);
