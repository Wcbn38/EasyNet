#include "Parser_WAVEDROM.h"
#include "Parser_DOT.h"
#include "iostream"

using namespace std;

void TB_Stimuli()
{
	map<time_t, list<STIMULI<LOGICSTATE>>*> stimuli;

	fstream tb1("DOT_TB0.dot", ios_base::in);

	set<NAMEDNET<LOGICSTATE>*> inNet;
	set<NAMEDNET<LOGICSTATE>*> outNet;

	parser_DOT(tb1, inNet, outNet);
	parser_WAVEDROM(fstream("STIMU_TB0.wave", ios_base::in), stimuli);

	time_t timestamp = 0;

	cout << " | ";

	for (auto netIT = inNet.begin(); netIT != inNet.end(); netIT++)
	{
		cout << (*netIT)->getName() << " | ";
	}

	cout << " | ";

	for (auto netIT = outNet.begin(); netIT != outNet.end(); netIT++)
	{
		cout << (*netIT)->getName() << " | ";
	}

	cout << endl;

	while (stimuli.size() > 0)
	{
		map<time_t, list<STIMULI<LOGICSTATE>>*>::iterator currStimuli = stimuli.find(timestamp);
		if (currStimuli != stimuli.end())
		{
			for (auto netUpdate = currStimuli->second->begin(); netUpdate != currStimuli->second->end(); netUpdate++)
			{
				netUpdate->net->setNetState(netUpdate->newState);
			}

			cout << " | ";

			for (auto netIT = inNet.begin(); netIT != inNet.end(); netIT++)
			{
				cout << (*netIT)->getNetState() << " | ";
			}

			cout << " | ";

			for (auto netIT = outNet.begin(); netIT != outNet.end(); netIT++)
			{
				cout << (*netIT)->getNetState() << " | ";
			}

			cout << endl;

			stimuli.erase(currStimuli->first);
		}

		timestamp++;
	}
}