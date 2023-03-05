#pragma once
#include<iostream>
using namespace std;

class Sum
{
private:
	int num, sum;
public:
	void Getnum();
	void Calculate(int num = 10);
	void Print();
	void PrintSum(int num = 10);
};

