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

	cout << "������ �Է��Ͻðڽ��ϱ�?(y/n) : ";
	cin >> select;

	if (select == 'y')
	{
		cout << "�����Է� : ";
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
	cout << "1 ~ " << num << "�� �� : " << sum << "\n";
}