#include <iostream>
#include "DefaultGates.h"

using namespace std;

void TB_MultiGates()
{
	//full adder
	NET<LOGICSTATE>* buff[2];

	NET<LOGICSTATE> A(X);
	NET<LOGICSTATE> B(X);
	NET<LOGICSTATE> Cin(X);

	buff[0] = &A; buff[1] = &B;
	XOR xor1(buff, "XOR_1");
	AND and1(buff, "AND_1");

	buff[0] = &Cin; buff[1] = xor1.getOutputNet(0);
	XOR xor2(buff, "XOR_2");
	AND and2(buff, "AND_2");

	buff[0] = and1.getOutputNet(0); buff[1] = and2.getOutputNet(0);
	OR or1(buff, "OR_1");

	cout << "|A|B|Cin| |S|Cout|" << endl;

	NET<LOGICSTATE>* S = xor2.getOutputNet(0);
	NET<LOGICSTATE>* Cout = or1.getOutputNet(0);

	A.setNetState(L0); B.setNetState(L0); Cin.setNetState(L0);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L0); B.setNetState(L0); Cin.setNetState(L1);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L0); B.setNetState(L1); Cin.setNetState(L0);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L0); B.setNetState(L1); Cin.setNetState(L1);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L1); B.setNetState(L0); Cin.setNetState(L0);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L1); B.setNetState(L0); Cin.setNetState(L1);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L1); B.setNetState(L1); Cin.setNetState(L0);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;

	A.setNetState(L1); B.setNetState(L1); Cin.setNetState(L1);
	cout << "|" << A.getNetState() << "|" << B.getNetState() << "|  " << Cin.getNetState() << "| ";
	cout << "|" << S->getNetState() << "|   " << Cout->getNetState() << "|";
	cout << endl;
}