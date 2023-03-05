#include<iostream>
using namespace std;

class Add
{
//아무것도 선언 안 하면 private이 기본이 된다.
public:
	void AddNum1(int Num = 10); //함수 원형에만 써야 한다.
	void AddNum2(int Num1 = 10, int Num2 = 5); //디폴트 매개변수를 사용할때는 오른쪽 끝에서부터
};
void Add::AddNum1(int Num)//여기 쓰면 기본 함수 재정의 라고 뜬다. //int Num2 = 5 //함수 원형에만 써야 한다.
{
	cout << Num << "+" << "1 = " << Num + 1 << endl;
}
void Add::AddNum2(int Num1, int Num2)
{
	cout << Num1 << "+" << Num2 << " = " << Num1 + Num2 << endl;
}
void main()
{
	Add add;
	add.AddNum1(); //호출 자체가 문제 그냥 문제가 있는 코드임 신경 xx
	add.AddNum1(20);
	add.AddNum2();
	add.AddNum2(20);
	add.AddNum2(10, 20);
}