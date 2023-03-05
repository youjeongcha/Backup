//다중 상속
//부모 class가 둘 이상으로 상속 받은 경우
//기본적으로 C++에서만 지원하며 다른 언어에서는 지양하는 편

#include <iostream>
using namespace std;

class A
{
public:
	void func()
	{
		cout << "A함수 입니다." << endl;
	}
};

class B
{
public:
	void func()
	{
		cout << "B함수 입니다." << endl;
	}
};

class C : public A, public B
{
public:
	void func3()
	{
		A::func();
		B::func();
	}

	/*
	void func3()
	{
		func();
		func();
	}//에러
	*/
};

void main()
{
	C c;
	c.func3();
}