//다중 상속
//부모 class가 둘 이상으로 상속 받은 경우
//기본적으로 C++에서만 지원하며 다른 언어에서는 지양하는 편

#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A함수 생성자." << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B함수 생성자." << endl;
	}
};

class C : public A
{
public:
	C()
	{
		cout << "C함수 생성자." << endl;
	}
};

class D : public B, public C
{
public:
	D()
	{
		cout << "D함수 생성자." << endl;
	}
};

void main()
{
	D d;
}