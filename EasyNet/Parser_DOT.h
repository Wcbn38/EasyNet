#pragma once
#include "Lexer.h"
#include "GenericGate.h"
#include "NamedNetGraph.h"
#include "DefaultGates.h"
#include <set>

//error ranges from 0x100 to 0x200
#define PARSE_ERROR_OFFSET

//error codes
#define PARSE_NO_ERROR PARSE_ERROR_OFFSET + 0x00
#define PARSE_CORRUPTED_FORMAT PARSE_ERROR_OFFSET + 0x01
#define PARSE_FAILED_TO_BUILD PARSE_ERROR_OFFSET + 0x02

#define PARSE_UNKNWON_ERROR PARSE_ERROR_OFFSET + 0xFF

struct ERROR
{
	std::string msg;
	int code;
};

const DELIM dot_delimiters[] = {
	//delimiters
	{" ", true},
	{"\n", true},
	{"\t", true},

	//keys
	{";", false},
	{"->", false},
	{"[", false},
	{"]", false},
	{"\"", false},
	{"=", false},
	{"{", false},
	{"}", false}
};

ERROR parser_DOT(std::fstream& file, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist);