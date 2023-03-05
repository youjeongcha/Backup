#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

class Wages
{
private:
	int time;
	int wage;
	int day;
public:
	void GetDay();
	void GetTime();
	void GetWage();
	int Calculate(int time, int wage);
	void Print();
	void Print2(char select, int time = 8, int wage = 9160);
};

