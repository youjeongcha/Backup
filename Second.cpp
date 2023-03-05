#include "Second.h"

void Second::Test2(string sA)
{
	cout << sA << " -> ";
	for (int i = sA.length() - 1; i >= 0; i--)
		cout << sA[i];
	cout << "\n";
}

void Second::Test2(string sA, string sB)
{
	cout << sA << " + " << sB << " : " << sA + sB << "\n";
}