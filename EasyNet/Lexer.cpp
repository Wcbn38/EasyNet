#include "Lexer.h"

int lex(std::fstream& file, DELIM_TYPE& delims, std::list<std::string>& lexedList)
{
	if (!file.is_open())
	{
		return LEX_FILE_NOT_OPENED;
	}

	std::string buffer;

	while (!file.eof())
	{
		buffer += file.get();
		if (file.gcount() <= 0) //EOF
			return LEX_SUCCESS;

		std::map<std::string, bool>::iterator findIT = delims.find(buffer);

		if (findIT != delims.end()) //delim found, add to list
		{
			if((buffer.size() - findIT->first.size()) > 0)
				lexedList.push_back(buffer.substr(0, buffer.size() - findIT->first.size()));

			if (!findIT->second)
				lexedList.push_back(findIT->first);

			buffer = "";
		}
	}

	if(buffer.size() > 0)
		lexedList.push_back(buffer);

	return LEX_SUCCESS;
}