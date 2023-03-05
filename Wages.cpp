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
	if (wage < 9160) //입력받는 옆에 예외처리하는 거 좋음
	{
		wage = 9160;
		cout << "시급 : " << wage << "\n";
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
	cout << "근무일수 : ";
	GetDay();
	cout << "시간과 임금을 입력하시겠습니까?(y/n) : ";
	cin >> select;
	if (select == 'y')
	{
		cout << "근무시간 : ";
		GetTime();
		cout << "시급 : ";
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
		cout << "시급 : " << wage << "\n";
	}
	cout << "일한 시간 : " << time << "시간" << " 일한 날자 : " << day << "일\n";
	cout << "총 급여 : " << Calculate(time, wage) << "원\n";
}