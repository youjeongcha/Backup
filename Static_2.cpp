#include <iostream>
using namespace std;
//class 내부 static 변수

class A//class는 멤버의 영역 원래는 전역 못 만든다. 그래서 int A::count = 0; 외부 선언 초기화 필요
	   //클래스는 설계도
{
public :
	static int count;//전역변수이다 보니 어느정도는 풀어도 상관없다
	//변수는 하나인데 A로 만들어진  a1,a2,a3들이 공용으로 사용
	A()
	{
		cout << ++count << endl;
	}
};
int A::count = 0; //본체. 클래스 내에서 전역을 사용하기 위해서는 외부에서 선언과 초기화 필요
void main()
{
	A a1; //10줄 > 그래서 다른 객체인데도 같이 사용 가능 
	A a2;
	A a3;
	A::count = 10; //public이라서 이렇게 가능
	A a4;
	A a5;
}