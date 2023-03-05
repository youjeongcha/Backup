#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

enum GUGUDAN
{
	GUGUDAN_START = 2,
	GUGUDAN_TWO = 2,
	GUGUDAN_THREE,
	GUGUDAN_FOUR,
	GUGUDAN_FIVE,
	GUGUDAN_SIX,
	GUGUDAN_SEVEN,
	GUGUDAN_EIGHT,
	GUGUDAN_NINE,
	GUGUDAN_END = GUGUDAN_NINE
};

class MultiplicationTable
{
private:
	int start, end;
public:
	void SetStart();
	void SetEnd();
	bool StartRangeCheck();
	bool EndRangeCheck();
	void Print();
	void PrintDan(int start = 2, int end = 9);
};
