#pragma once
#include"Wages.h"
#include"Sum.h"
#include"MultiplicationTable.h"
#include<Windows.h>

int Menu()
{
	int select;

	cout << "DefaultParameter ����\n";
	cout << "1.�޿����\n";
	cout << "2.�����հ�\n";
	cout << "3.���������\n";
	cout << "4.����\n";
	cout << "���� : ";
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