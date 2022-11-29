#pragma once
#include "Lexer.h"
#include <fstream>
#include "Parse.h"
#include <list>
#include "Stimuli.h"
#include <set>

const DELIM wavdrom_delimiters[] = {
	//delimiters
	{" ", DISCARD},
	{"\n", DISCARD},
	{"\t", DISCARD},

	//keys
	{",", DISCARD},
	{"[", SAVE},
	{"]", SAVE},
	{"\"", TOGGLE_STRING},
	{"'", TOGGLE_STRING},
	{":", DISCARD},
	{"{", SAVE},
	{"}", SAVE}
};

ERROR parser_WAVEDROM(std::fstream& file, std::map<time_t, std::list<STIMULI<LOGICSTATE>>*>& stimuli);