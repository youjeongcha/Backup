#include <iostream>
using namespace std;

void func(int& ref)
{//ref는 a를 참조하고 있는 중.
	//한번 초기 변수를 지정하면 끝날때까지 변수를 가리킨다.
	//포인터는 참조하는 변수 변경이 가능하다. (자료구조 좀더 디테일하게 관리)
	cout << "ref = " << ref << endl << endl;
	int b = 20;
	ref = b; //b의 내용물을 a메모리에 저장하는 것
	b = 25;
	cout << "b = " << b << endl;
	cout << "ref = " << ref << endl;
}

void main()
{
	int a = 10;
	cout << "a = " << a << endl;
	func(a);
	cout << "a = " << a << endl;
}