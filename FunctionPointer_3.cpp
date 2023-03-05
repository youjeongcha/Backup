#include<iostream>
#include<functional>
using namespace std;
//람다식 (이름이 없는 함수. 익명의 함수)
//일회용 함수 . 재활용이 불가

void Subfunc(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void func2(function<void(int, int)> p)
{
	p(15, 10);
}
void main()
{
	func2([](int x, int y) {//[]gkrh dlswk gkaus 
		//이때만 잠깐 쓰고 버리는 함수
		cout << x << "+" << y << "=" << x + y << endl;
		});
	func2(Subfunc);
	return;
}