#include<iostream>
using namespace std;

void func(int n = 10) //디폴트 매개변수
{
	int Sum = 0;
	for (int i = 1; i <= n; i++)
		Sum += i;
	cout << "1 ~" << n << "까지의 총 합 : " << Sum << endl;
}

void main()
{
	func(100);
	func();
}