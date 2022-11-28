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

struct DELIM
{
	std::string tag;
	DELIM_MODE mode;
};

const DELIM dot_delimiters[] = {
	//delimiters
	{" ", DISCARD},
	{"\n", DISCARD},
	{"\t", DISCARD},

	//keys
	{";", SAVE},
	{"->", SAVE},
	{"[", SAVE},
	{"]", SAVE},
	{"\"", SAVE},
	{"=", SAVE},
	{"{", SAVE},
	{"}", SAVE}
};

/**
Parses a DOT file. Every node can only have 2 inputs and 1 output.
\param file: file to parse.
\param innetlist: input net list for stimulation. Every net has the X state.
\param outnetlist: output net list for acquisition.
*/
ERROR parser_DOT(std::fstream& file, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist);