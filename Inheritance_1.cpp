#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A Class ����" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B Class ����" << endl;
	}
};

void main()
{
	B b;
}