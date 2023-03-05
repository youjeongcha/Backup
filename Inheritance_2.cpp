#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A Class 생성" << endl;
	}
	~A()
	{
		cout << "A의 소멸자 호출" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B Class 생성" << endl;
	}
	~B()
	{
		cout << "B의 소멸자 호출" << endl;
	}
};

void main()
{
	B b;
}