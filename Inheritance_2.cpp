#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A Class ����" << endl;
	}
	~A()
	{
		cout << "A�� �Ҹ��� ȣ��" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B Class ����" << endl;
	}
	~B()
	{
		cout << "B�� �Ҹ��� ȣ��" << endl;
	}
};

void main()
{
	B b;
}