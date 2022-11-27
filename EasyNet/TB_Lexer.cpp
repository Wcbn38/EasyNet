#include "Lexer.h"
#include "iostream"

using namespace std;

void TB_Lexer()
{
	list<string> lexedList;
	DELIM_TYPE delims;

	//to discard
	delims.insert({ " ", true });
	delims.insert({ "{", false });
	delims.insert({ "}", false });
	delims.insert({ "\t", true });
	delims.insert({ "[", true });
	delims.insert({ "]", true });
	delims.insert({ "=", false });
	delims.insert({ ";", false });
	delims.insert({ "\n", true });

	for (DELIM_TYPE::iterator it = delims.begin(); it != delims.end(); it++)
	{
		cout << it->first << endl;
	}

	//test
	cout << "************DOT_TB0.dot******************" << endl;
	fstream tb0("DOT_TB0.dot", ios_base::in);

	lex(tb0, delims, lexedList);

	for (list<string>::iterator it = lexedList.begin(); it != lexedList.end(); it++)
	{
		cout << *it << endl;
	}
	
	cout << "************DOT_TB1.dot******************" << endl;
	lexedList.clear();
	fstream tb1("DOT_TB1.dot", ios_base::in);

	lex(tb1, delims, lexedList);

	for (list<string>::iterator it = lexedList.begin(); it != lexedList.end(); it++)
	{
		cout << *it << endl;
	}
}