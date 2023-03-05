#pragma once

#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
using namespace std;

struct Position
{
	int m_ix;
	int m_iy;
};

struct Rectingle
{
	int m_iLeft;
	int m_iRight;
	int m_iUp;
	int m_iDown;
};

struct Size
{
	int m_iWidth;
	int m_iHeight;
};