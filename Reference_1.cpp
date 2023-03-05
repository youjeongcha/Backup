#include <iostream>
using namespace std;
//레퍼런스 - 특정한 변수의 이름에 다른 이름(별명)을 부여한다.
/* 별명은 define, typedef, enum, enum class가 있었는데. 이건 편의를 위해
reference는 기능을 위해서

포인터와 유사. 변수 선언할때 무조건 초기값을 넣어줘야 한다.
참조형 변수.*/
//함수에서 매개변수를 레퍼런스 변수로 인자값을 받을 경우 인자의 원본으로 정보처리를 진행한다.

//형식 - 자료형 & 변수명 = 변수;

void func(int& ref) //레퍼런스 자료형& 변수명
{//레퍼런스 변수가 인자면. 같은 메모리의 이름이 두개가 된 것.
	cout << "ref = " << ref << endl;
	ref = 20;
}//함수가 종료가 되어도 이름만 날아가고 메모리는 그대로

void main()
{
	int Sum = 10;
	cout << "Sum = " << Sum << endl;
	func(Sum);//주소를 보내지 않았는데도 포인터처럼 처리를 하고 있다.
	cout << "Sum = " << Sum << endl;
}