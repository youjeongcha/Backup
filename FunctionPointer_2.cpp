#include<iostream>
#include<functional>
using namespace std;
//특정 상황에 어떠한 동작을 하는데. 상황에 따라 달라져야 하는 함수

void Addfunc(int x, int y)
{
	cout << x << "+" << y << "=" << x + y << endl;
}
void Subfunc(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void func2(function<void(int, int)> p) //상황에 따라 동작되는 방식이 달라진다.(함수 포인터의 핵심)
//캐릭터 이동 모션
{
	p(15, 10);
}
void main()
{
	func2(Addfunc);
	func2(Subfunc);
	return;
}