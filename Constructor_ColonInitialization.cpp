#include<iostream>
using namespace std;

class A
{
private:
	const int m_iNum1; //const변수 해당 변수를 정보의 변경이 불가능한 상수로 변환한다.
	int m_iNum2;
public:
	A(int Num1, int Num2) : m_iNum1(Num1) //괄호 안에 초기화 하고 싶은 값
		//:뒤에 먼저가 호출되서 실행된다.
	{
		//m_iNum1 = Num1; //오류 : 식이 수정할 수 있는 Ivalue여야 합니다.
		m_iNum2 = Num2;
	}
	void print()
	{
		cout << "const int m_iNum1 = " << m_iNum1 << endl;
		cout << "int m_iNum2 = " << m_iNum2 << endl;
	}
};

void main()
{
	A a(10, 20);
	a.print();
}