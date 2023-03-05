#include<iostream>
using namespace std;

class Test
{
public:
	void test();
	void test(int num);
};

void Test::test()
{
	cout << "test()함수 호출" << endl;
}

void Test::test(int num)
{
	cout << "test(int num)함수 호출" << endl;
}

void main()
{
	Test t;
	t.test();
	t.test(10);
}