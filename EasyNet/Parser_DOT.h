#pragma once
#include "Lexer.h"
#include "GenericGate.h"
#include "NamedNetGraph.h"
#include "DefaultGates.h"
#include <set>
#include "Parse.h"

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
	{"\"", TOGGLE_STRING},
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