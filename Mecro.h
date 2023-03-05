#pragma once
#include<iostream>
#include<string>
#include<conio.h>//getch()이용
#include<iomanip>//cout로 서식문자 출력할때(신경 안 써도 됨)
#include<Windows.h>
using namespace std;

#define MAPMAX 20


struct Position
{
	int m_ix;
	int m_iy;
};

struct Rectingle
{//차이점
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

//----------------------

enum XY
{
	X,
	Y
};

enum DIRECTION
{
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's',

	BACK = 'n',
	ENTER = '\r',
	ESC = '\x1b'
};

//---------------

enum CHARATER
{
	BLACK,
	WHITE
};

class Mecro
{
public:
	//static 함수 집합체로 쓰려고. 해당 함수가 객체로써의 의미가 없기 때문에 static으로 사용하는 것이 맞다.
	inline static void gotoxy(int x, int y) //inline 해당함수 호출부분 생략. 호출 전에 미리 data 영역에 메모리를 올려둔다. 빠른 호출 가능
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	inline static void DrawPoint(string str, int x, int y)
	{//특수문자는 일반문자의 두배. 특수문자 기준으로 바꿔준다.
		gotoxy(x * 2, y);
		cout << str;
		return;
	}
	inline static void DrawMidText(string str, int x, int y)
	{//중간기준 출력 //중앙정렬
		if (x > str.size() / 2)
			x -= str.size() / 2;//반만큼 땡긴다.
		gotoxy(x, y);
		cout << str;
		return;
	}
	inline static void TextDraw(string str, int x, int y)
	{//좌측 기준 출력 //좌측정렬
		gotoxy(x, y);
		cout << str;
	}
	inline static void ErasePoint(int x, int y)
	{
		for (int i = y; i <= y + 4; i++)
		{
			gotoxy(x * 2, i);
			cout << "                                      ";
		}
		return;
	}
};
