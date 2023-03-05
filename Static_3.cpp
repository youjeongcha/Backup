#include<iostream>
using namespace std;

class A
{
private:
	int Num; 
public :
	static int count;//헤더로 .h로 작성
	A()
	{
		Num = 10;
		cout << ++count << endl;
	}
	static void Print()
		//일반적으로는 class 안에 속하니 멤버 함수라고 한다.
	
	{
		cout << "count : " << count << endl;//본디 호출한 객체에 소속
		//count를 static으로 하지 않으면 공용으로 사용해서 a1,a2,a3 어느 쪽의인지 객체인지 몰라 사용 불가.
		//static함수에서는 static 변수만 사용가능
	}
};
int A::count = 0;//.cpp에 작성
void main()
{
	A a1;
	A a2;
	A::count = 10;
	A a3;
	A a4;
	A a5;
	a5.Print();
	A::Print();//공용이기에 이렇게도 사용가능
}