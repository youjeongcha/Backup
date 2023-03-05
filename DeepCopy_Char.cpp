#include<iostream>
using namespace std;

void main()
{
	char str[6] = "Hello";
	char tmp[6];
	//
	for (int i = 0; i < 6; i++)
		tmp[i] = str[i];
	//
	cout << "str = " << str << endl;
	cout << "tmp = " << tmp << endl;
	strcpy(str, "Bye");
	cout << "str = " << str << endl;
	cout << "tmp = " << tmp << endl;
	
	return;
}