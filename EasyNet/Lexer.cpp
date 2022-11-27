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
		std::set<DELIM, DELIM_CMP>::iterator findIT = delims.find(buffer);

		if (findIT != delims.end()) //delim found, add to list
		{
			if((buffer.size() - findIT->tag.size()) > 0)
				lexedList.push_back(buffer.substr(0, buffer.size() - findIT->tag.size()));

			if (!findIT->discard)
				lexedList.push_back(findIT->tag);

			buffer = "";
		}
	}

	lexedList.push_back(buffer);

	return LEX_SUCCESS;
}

bool DELIM_CMP::operator() (DELIM const& o1, DELIM const& o2) const
{
	return o1.tag < o2.tag;
}

bool DELIM_CMP::operator() (DELIM const& del, const std::string str) const //higher
{
	if (del.tag.size() > str.size())
		return true;

	return str.substr(str.size() - del.tag.size()) > del.tag;
}

bool DELIM_CMP::operator() (const std::string str, DELIM const& del) const //lower
{
	if (del.tag.size() > str.size())
		return false;

	return str.substr(str.size() - del.tag.size()) < del.tag;
}