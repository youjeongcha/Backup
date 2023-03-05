#include<iostream>
using namespace std;

bool func(int num)
{
	bool b;
	if (num == 10)
		b = true; //true 는 1
	else
		b = false; //false 는 0
	return b; //1byte
}

void main()
{
	int num;
	cout << "10을 입력하시오" << endl;
	cin >> num;
	cout << func(num);
}