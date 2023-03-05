#pragma once
#include <iostream>
#include <string>
#include <list>
#include <Windows.h> //gotoxy COORD �̿뿡 �ʿ�
#include <conio.h>  //kbhit
//#include <functional> //�Լ�������
using namespace std;

#define WIDTH 50
#define HEIGHT 30

struct XY
{
	int x;
	int y;
};

enum PATERN
{
	PATERN_APPOINT,
	PATERN_RANDOM
};

inline static void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

inline static void DrawMidText(string str, int x, int y)
{
	if ((x > str.size() / 2))
		x -= str.size() / 2; //�ݸ�ŭ �����
	gotoxy(x, y);
	cout << str;
}