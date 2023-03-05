#include<iostream>
using namespace std;

class calc
{
private:
	int num1;
	int num2;
public:
	void Seltdate(int num1, int num2)//멤버 변수에 데이터 안 들어감. 멤버랑 이름이 같으면 멤버 우선
	{
		this -> num1 = num1;
		this -> num2 = num2;
	}
	int GetSum()
	{
		return num1 + num2;
	}
	void PrintAddress()
	{
		cout << "Address : " << this << endl;
	}
};

void main()
{
	//int su1, su2;
	calc ca1;
	calc ca2;
	cout << "ca1 Address: " << &ca1 << endl;//호출하는 변수에 따라 상대적이다.
	ca1.PrintAddress();
	cout << "ca2 Address: " << &ca2 << endl;
	ca2.PrintAddress();
	//cin >> su1 >> su2;
	//ca.Seltdate(su1, su2);
	//cout << su1 << " + " << su2 << " = " << ca.GetSum();
}