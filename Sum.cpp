#include "Sum.h"

void Sum::Getnum()
{
	cin >> num;
}

void Sum::Calculate(int num)
{
	sum = 0;
	for (int i = 1; i <= num; i++)
		sum += i;
}

void Sum::Print()
{
	char select;

	cout << "정수를 입력하시겠습니까?(y/n) : ";
	cin >> select;

	if (select == 'y')
	{
		cout << "정수입력 : ";
		Getnum();
		Calculate(num);
		PrintSum(num);
	}
	else
	{
		Calculate();
		PrintSum();
	}
}

void Sum::PrintSum(int num)
{
	cout << "1 ~ " << num << "총 합 : " << sum << "\n";
}