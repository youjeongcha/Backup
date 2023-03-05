#include<iostream>
using namespace std;

class Test
{
public:
	void test(int a, int b = 100);
	void test(int a);
};

void Test::test(int a, int b)
{
	cout << "디폴트 인자 함수 호출" << endl;
}

void Test::test(int a)
{
	cout << "오버로딩 함수 호출" << endl;
}

void main()
{
	Test t;
	t.test(10); //오버로드된 함수 "Test::test"의 인스턴스 중 두 개 이상이 인수 목록과 일치합니다.
}