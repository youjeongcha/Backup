#include<iostream>
#include<string>
using namespace std;

void main()
{
	string str = "Hello";
	char* arr = (char*)str.c_str();
	cout << "str = " << str << endl;
	cout << "arr = " << arr << endl;
	str = "Bye";
	cout << "str = " << str << endl;
	cout << "arr = " << arr << endl;
}