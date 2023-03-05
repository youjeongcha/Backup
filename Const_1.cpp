#include<iostream>
using namespace std;
//const 변수
//해당 변수를 정보의 변경이 불가능한 상수로 변환한다.

void main()
{
	const int Num = 10;
	Num = 20; //오류 : 식이 수정할 수 있는 lvalue여야 합니다.
	//변수를 상수화시킨다.
}