#include<iostream>
using namespace std;

bool func(int num)
{
	bool b;
	if (num == 10)
		b = true; //true �� 1
	else
		b = false; //false �� 0
	return b; //1byte
}

void main()
{
	int num;
	cout << "10�� �Է��Ͻÿ�" << endl;
	cin >> num;
	cout << func(num);
}