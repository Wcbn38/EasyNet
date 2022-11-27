#include "Parser_DOT.h"
#include "iostream"
#include "NamedNetGraph.h"

using namespace std;

void TB_DotParser()
{
	fstream tb1("DOT_TB1.dot", ios_base::in);

	set<NAMEDNET<LOGICSTATE>*> inNet;
	set<NAMEDNET<LOGICSTATE>*> outNet;

	ERROR iResult = parser_DOT(tb1, inNet, outNet);

	cout << "[" << iResult.code << "]" << iResult.msg << endl;
}