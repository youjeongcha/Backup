#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A Class 持失" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B Class 持失" << endl;
	}
};

void main()
{
	B b;
}