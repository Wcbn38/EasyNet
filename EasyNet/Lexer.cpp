#include "Lexer.h"

#include "lexer.h"

int lex(std::fstream& file, DELIM_MAP& delimiters, LEXED_LIST& lexListContainer)
{
	if (!file.is_open())
		return LEX_FILE_NOT_OPENED;

	std::string buf;
	int iResult = file.get();

	while (iResult != EOF)
	{
		buf += iResult;

		DELIM_MAP::iterator delimSearch;
		for (delimSearch = delimiters.begin(); delimSearch != delimiters.end(); delimSearch++)
			if (delimSearch->first.size() <= buf.size())
				if (delimSearch->first == buf.substr(buf.size() - delimSearch->first.size()))
					break;

		if (delimSearch != delimiters.end())
		{
			if ((buf.size() - delimSearch->first.size()) > 0)
				lexListContainer.push_back(buf.substr(0, buf.size() - delimSearch->first.size()));

			if (delimSearch->second == SAVE)
				lexListContainer.push_back(delimSearch->first);

			buf = ""; //reset buffer
		}

		iResult = file.get();
	}

	lexListContainer.push_back(buf);

	return LEX_SUCCESS;
}