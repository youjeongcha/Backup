#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;
class Number
{
private:
	char* m_czNumber;
public:
	Number();
	void NumberDraw();
	void SetNumber(int FirstBar, int SecondBar, string str);
	~Number();
};

