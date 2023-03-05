#include<iostream>
#include<functional>
using namespace std;
//Bind(특정 인자를 고정)
//default매개 변수와 유사

void Addfunc1(int x1, int x2, int x3, int x4)
{
	cout << x1 << "+" << x2 << "=" << x3 + x4 << endl;
}
void Addfunc(int x, int y)
{
	cout << x << "+" << y << "=" << x + y << endl;
}
void Subfunc(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void func2(function<void(int)> p)//인자하나짜리
{
	p(20);
}
void main()
{
	//하나 고정 placeholders::_1
	func2(bind(Addfunc, 10, placeholders::_1));//함수명, 실제 인자값(첫번째 인자 x에 고정), 고정 안시킨 거. intp가 _1을 의미
	func2(bind(Subfunc, 10, placeholders::_1));

	func2(bind(Addfunc1, 1, 2, placeholders::_1, 3)); //x3을 20으로 고정
	//고정 시킬 거 placeholders::_3개면 1 ~ placeholders::_3으로도 사용 가능
	return;
}