#include<iostream>
#include<string>
using namespace std;

void main()
{
	string s1;
	string s2 = "123";
	string s3 = "Hello";
	string s4 = "æ»≥Á«œººø‰";
	cout << "s1 = " << s1.length() << endl;
	cout << "s2 = " << s2.length() << endl;
	cout << "s3 = " << s3.length() << endl;
	cout << "s4 = " << s4.length() << endl;

	cout << "s4 = " << s4.size() << endl;
	return;
}