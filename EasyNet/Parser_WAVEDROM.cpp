#include "Parser_WAVEDROM.h"

bool getLogic(char id, LOGICSTATE& state, bool& toggleState)
{
	switch (id)
	{
	case '.':
		if (toggleState)
			state = state ^ L0;
		break;
	case 'p':
	case 'P':
		state = L1; toggleState = true;
		break;
	case 'n':
	case 'N':
		state = L0; toggleState = true;
		break;
	case 'h':
	case 'H':
		state = L1; toggleState = false;
		break;
	case 'l':
	case 'L':
		state = L0; toggleState = false;
		break;
	case '0':
		state = L0; toggleState = false;
		break;
	case '1':
		state = L1; toggleState = false;
		break;
	case 'x':
	case 'X':
		state = X; toggleState = false;
		break;
	case 'z':
	case 'Z':
		state = Z; toggleState = false;
		break;
	default:
		return false;
	}

	return true;
}

ERROR parser_WAVEDROM(std::fstream& file, std::map<time_t, std::list<STIMULI<LOGICSTATE>>*>& stimuli)
{
	//lexer
	DELIM_MAP delims;
	std::list<std::string> lexedList;

	for (int i = 0; i < (sizeof(wavdrom_delimiters) / sizeof(DELIM)); i++)
		ADD_DELIM(delims, wavdrom_delimiters[i].tag, wavdrom_delimiters[i].mode);

	switch (lex(file, delims, lexedList))
	{
	case LEX_SUCCESS:
		break;
	case LEX_FILE_NOT_OPENED:
		return { "Input file is not readable", LEX_FILE_NOT_OPENED };
	default:
		return { "UNKNWON_ERROR", PARSE_UNKNWON_ERROR };
	}

	if (lexedList.front() != "{")
		return { "Missing token.", PARSE_CORRUPTED_FORMAT };
	lexedList.pop_front();

	while ((lexedList.front() != "}") && (lexedList.size() > 0))
	{
		std::string mainProperty = lexedList.front();
		lexedList.pop_front();

		if (mainProperty == "signal")
		{
			if (lexedList.front() != "[")
				return { "Missing token.", PARSE_CORRUPTED_FORMAT };
			lexedList.pop_front();

			while (lexedList.front() != "]")
			{
				if (lexedList.front() != "{")
					return { "Missing token.", PARSE_CORRUPTED_FORMAT };
				lexedList.pop_front();

				NAMEDNET<LOGICSTATE>* currentNet = NULL;
				std::string states;

				while (lexedList.front() != "}")
				{
					std::string propKey = lexedList.front();
					lexedList.pop_front();

					std::string propValue = lexedList.front();
					lexedList.pop_front();

					if (propKey == "name")
					{
						std::pair<bool, NAMEDNET<LOGICSTATE>*> foundNet = NAMEDNET<LOGICSTATE>::getObjWithName("\\NET_" + propValue + "_0");
						if (foundNet.first == false)
							return { "No net found with this name", PARSE_NOT_FOUND };

						currentNet = foundNet.second;
					}
					else if (propKey == "wave")
					{
						states = propValue;
					}
				}
				lexedList.pop_front();

				if(currentNet == NULL)
					return { "No net specified.", PARSE_NOT_FOUND };

				time_t timestamp = 0;
				LOGICSTATE currState = X, nextState = X;
				bool lastStateToggle = false;

				while (states.size() > 0)
				{
					if (!getLogic(states.front(), nextState, lastStateToggle))
						return { "Invalid net stimuli state.", PARSE_CORRUPTED_FORMAT };

					if (currState != nextState)
					{
						std::map<time_t, std::list<STIMULI<LOGICSTATE>>*>::iterator getTimestamp = stimuli.find(timestamp);
						if (getTimestamp == stimuli.end())
						{
							stimuli.insert({ timestamp, new std::list<STIMULI<LOGICSTATE>>});
							getTimestamp = stimuli.find(timestamp);
						}

						getTimestamp->second->push_back({ currentNet, nextState });
						currState = nextState;
					}

					timestamp++;

					if (states.size() > 1)
						states = states.substr(1);
					else
						states = "";
				}
			}
			lexedList.pop_front();
		}
		else
			return { "Property is not supported.", PARSE_CORRUPTED_FORMAT};
	}

	if (lexedList.front() != "}")
		return { "Missing token.", PARSE_CORRUPTED_FORMAT };
	lexedList.pop_front();

	return { "", PARSE_NO_ERROR };
}