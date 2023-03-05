#include "First.h"

void First::Test(int iA, int iB)
{
	int sum = iA
		;
	for (int i = 1; i < iB; i++)
		sum *= iA;

	cout << iA << "ÀÇ " << iB << "½Â : " << sum << "\n";
}

void First::Test(int iA, char sC)
{
	char cTemp = char(sC + iA);

	if (cTemp > 'z' || cTemp > 'Z')
		cTemp -= 26;


	cout << sC << " >> " << iA << " : " << cTemp << "\n";
}