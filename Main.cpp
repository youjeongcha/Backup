#pragma once
#include"Wages.h"
#include"Sum.h"
#include"MultiplicationTable.h"
#include<Windows.h>

int Menu()
{
	int select;

	cout << "DefaultParameter 문제\n";
	cout << "1.급여계산\n";
	cout << "2.누적합계\n";
	cout << "3.구구단출력\n";
	cout << "4.종료\n";
	cout << "선택 : ";
	cin >> select;

	return select;
}

void main()
{
	Sum sum;
	MultiplicationTable GuguDan;
	Wages wages;

	while (true)
	{
		switch (Menu())
		{
		case 1:
			wages.Print();
			break;
		case 2:
			sum.Print();
			break;
		case 3:
			GuguDan.Print();
			break;
		case 4:
			return;
		}
		system("pause");
		system("cls");
	}
}