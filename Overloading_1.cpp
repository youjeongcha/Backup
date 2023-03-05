#include<iostream>
using namespace std;

void func()
{
	cout << "func1() 함수를 호출하였습니다." << endl;
}

void func(int a)
{
	cout << "func1(int a) 함수를 호출하였습니다." << endl;

}

void main()
{
	func();
	func(10);
}