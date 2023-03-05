#include <iostream>
#include <functional> //라이브러리. c++ stl 함수 관련 기능들이 들어있다.
using namespace std;
//함수 포인터의 장점 : 상황에 따라 얼마든지 달리질 수 있다.

void func1()
{
	cout << "함수 포인터1 호출" << endl;
}

void func2()
{
	cout << "함수 포인터2 호출" << endl;
}

void main()
{
	//list<int>
	function<void()> p; // <반환자료형(매개변수)> 

	p = func1;// <반환자료형(매개변수)>  동일
	p();

	//변수의 장점. 저장된 데이터를 얼마든지 바꿀 수 있다.
	p = func2;
	p();

	return;
}