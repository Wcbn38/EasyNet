#include "Parser_DOT.h"
#include <set>
#include <map>

struct DOT_OBJ
{
	std::vector<std::string> inputs;
	std::string label;
};

template <typename TSTATE>
bool operator<(const NAMEDNET<TSTATE>& n1, const NAMEDNET<TSTATE>& n2)
{
	return n1.getName() < n2.getName();
}

ERROR parse_graph(std::map<std::string, DOT_OBJ>& objList, std::list<std::string>& lexedList, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist);
ERROR parse_obj(std::map<std::string, DOT_OBJ>& objList, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist);

ERROR parser_DOT(std::fstream& file, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist)
{
	//lexer
	DELIM_MAP delims;
	std::list<std::string> lexedList;
	
	for (int i = 0; i < (sizeof(dot_delimiters) / sizeof(DELIM)); i++)
		ADD_DELIM(delims, dot_delimiters[i].tag, dot_delimiters[i].mode);

	switch (lex(file, delims, lexedList))
	{
	case LEX_SUCCESS: 
		break;
	case LEX_FILE_NOT_OPENED:
		return { "Input file is not readable", LEX_FILE_NOT_OPENED };
	default:
		return { "UNKNWON_ERROR", PARSE_UNKNWON_ERROR };
	}

	//parsing
	//getting graph name
	std::string graphName;

	if (lexedList.front() != "digraph")
		return { "Missing keyword.", PARSE_CORRUPTED_FORMAT };
	lexedList.pop_front();

	graphName = lexedList.front();
	lexedList.pop_front();

	std::map<std::string, DOT_OBJ> objList;

	parse_graph(objList, lexedList, innetlist, outnetlist); //TODO: while true or something like that should work
	parse_obj(objList, innetlist, outnetlist);

	return { "Success", PARSE_NO_ERROR };
}

ERROR parse_graph(std::map<std::string, DOT_OBJ>& objList, std::list<std::string>& lexedList, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist)
{
	if (lexedList.front() != "{")
		return { "Missing '{'.", PARSE_CORRUPTED_FORMAT };
	lexedList.pop_front();

	while (lexedList.front() != "}" || lexedList.size() == 0)
	{
		auto currObj = objList.find(lexedList.front());

		if (currObj == objList.end()) //create object
			currObj = objList.insert({ lexedList.front(), {} }).first;

		lexedList.pop_front();

		if (lexedList.front() == "[") //change properties
		{
			lexedList.pop_front();
			while (lexedList.front() != "]")
			{
				std::string property = lexedList.front();
				lexedList.pop_front();

				if (lexedList.front() != "=")
					return { "Invalid token.", PARSE_CORRUPTED_FORMAT };
				lexedList.pop_front();

				if (lexedList.front() != "\"")
					return { "Missing '\"'.", PARSE_CORRUPTED_FORMAT };
				lexedList.pop_front();

				std::string attribute = lexedList.front();
				lexedList.pop_front();

				if (lexedList.front() != "\"")
					return { "Missing '\"'.", PARSE_CORRUPTED_FORMAT };
				lexedList.pop_front();

				if (property == "label")
					currObj->second.label = attribute;
				else
					return { "Unknown property", PARSE_CORRUPTED_FORMAT };
			}
			lexedList.pop_front();
		}
		else if (lexedList.front() == "->")
		{
			while (lexedList.front() == "->")
			{
				lexedList.pop_front();

				auto recvObj = objList.find(lexedList.front());

				if (recvObj == objList.end()) //create object
					recvObj = objList.insert({ lexedList.front(), {} }).first;

				lexedList.pop_front();

				recvObj->second.inputs.push_back(currObj->first);
				currObj = recvObj;
			}
		}
		else
		{
			return { "Unknown token.", PARSE_CORRUPTED_FORMAT };
		}

		if(lexedList.front() != ";")
			return { "Missing token ';'.", PARSE_CORRUPTED_FORMAT };
		lexedList.pop_front();
	}

	if (lexedList.front() != "}")
		return { "Missing '}'.", PARSE_CORRUPTED_FORMAT };
	lexedList.pop_front();

	return { "", PARSE_NO_ERROR };
}

ERROR constructGateObj(std::map<std::string, DOT_OBJ>::iterator obj, std::map<std::string, DOT_OBJ>& objMap, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist)
{
	if (obj->second.label != "INPUT")
	{
		std::vector<NAMEDNET<LOGICSTATE>*> inputNets;

		for (std::vector<std::string>::iterator it = obj->second.inputs.begin(); it != obj->second.inputs.end(); it++)
		{
			std::pair<bool, NAMEDNET<LOGICSTATE>*> netRes = NAMEDNET<LOGICSTATE>::getObjWithName("\\NET_" + *it + "_0");

			if (netRes.first == false)
			{
				std::map<std::string, DOT_OBJ>::iterator connObj = objMap.find(*it);
				if (connObj == objMap.end())
				{
					return { "Linker error, target not found.", PARSE_FAILED_TO_BUILD };
				}

				constructGateObj(connObj, objMap, innetlist, outnetlist);

				netRes = NAMEDNET<LOGICSTATE>::getObjWithName("\\NET_" + *it + "_0");

				if (netRes.first == false)
				{
					return { "Failed to build gate.", PARSE_FAILED_TO_BUILD };
				}
			}

			inputNets.push_back(netRes.second);
		}

		if (obj->second.label == "AND") {
			new AND(inputNets, obj->first);
		}
		else if (obj->second.label == "OUTPUT") {
			if (inputNets.size() != 1)
				return { "Output not has multiple connections.", PARSE_FAILED_TO_BUILD };
			outnetlist.insert(inputNets[0]);
		} else {
			return { "GATE NOT FOUND", PARSE_FAILED_TO_BUILD };
		}

		objMap.erase(obj);
	}
	else
	{
		innetlist.insert(new NAMEDNET<LOGICSTATE>(X, "\\NET_" + obj->first + "_0"));
		objMap.erase(obj);
	}

	return { "NO ERRORS", PARSE_NO_ERROR };
}

ERROR parse_obj(std::map<std::string, DOT_OBJ>& objList, std::set<NAMEDNET<LOGICSTATE>*>& innetlist, std::set<NAMEDNET<LOGICSTATE>*>& outnetlist)
{
	while (objList.size() > 0)
	{
		std::map<std::string, DOT_OBJ>::iterator currentObj = objList.begin();

		//create iterator
		constructGateObj(currentObj, objList, innetlist, outnetlist);
	}

	return { "", PARSE_NO_ERROR };
}