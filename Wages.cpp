#include "Wages.h"

void Wages::GetDay()
{
	cin >> day;
}

void Wages::GetTime()
{
	cin >> time;
}

void Wages::GetWage()
{
	cin >> wage;
	if (wage < 9160) //�Է¹޴� ���� ����ó���ϴ� �� ����
	{
		wage = 9160;
		cout << "�ñ� : " << wage << "\n";
	}
}

int Wages::Calculate(int time, int wage)
{
	int totalWage = wage * time * day;

	return totalWage;
}

void Wages::Print()
{
	char select;
	cout << "�ٹ��ϼ� : ";
	GetDay();
	cout << "�ð��� �ӱ��� �Է��Ͻðڽ��ϱ�?(y/n) : ";
	cin >> select;
	if (select == 'y')
	{
		cout << "�ٹ��ð� : ";
		GetTime();
		cout << "�ñ� : ";
		GetWage();
		Print2(select, time, wage);
	}
	else
	{
		Print2(select);
	}
}

void Wages::Print2(char select, int time, int wage)
{
	if (select != 'y')
	{
		cout << "�ñ� : " << wage << "\n";
	}
	cout << "���� �ð� : " << time << "�ð�" << " ���� ���� : " << day << "��\n";
	cout << "�� �޿� : " << Calculate(time, wage) << "��\n";
}