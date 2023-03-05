#pragma once
#include"Mecro.h"

class DrawManager
{
public:
	//static 함수 집합체로 쓰려고. 해당 함수가 객체로써의 의미가 없기 때문에 static으로 사용하는 것이 맞다.

	void static BoxDraw(int Start_x, int Start_y, int Width, int Height)
	{
		for (int y = 0; y < Height; y++)
		{
			gotoxy(Start_x, Start_y + y);
			if (y == 0)
			{
				cout << "┌";
				for (int x = 1; x < Width - 1; x++)
					cout << "┬";
				cout << "┐";
			}
			else if (y == Height - 1)
			{
				cout << "└";
				for (int x = 1; x < Width - 1; x++)
					cout << "┴";
				cout << "┘";
			}
			else
			{
				cout << "├";
				for (int x = 1; x < Width - 1; x++)
					cout << "┼";
				cout << "┤";
			}
		}
		return;
	}

	//------------------------------------------

	string static MapDraw(int m_x, int m_y)
	{//static은 static끼리 참조 가능
		if (m_y == 0)
			return MapDrawPart(m_x, "┌", "┐", "┬");
		else if (m_y == MAPMAX - 1)
			return MapDrawPart(m_x, "└", "┘", "┴");
		else
			return MapDrawPart(m_x, "├", "┤", "┼");
	}

	string static MapDrawPart(int m_x, string part1, string part2, string part3)
	{
		if (m_x == 0)
			return part1;
		else if (m_x == MAPMAX - 1)
			return part2;
		else
			return part3;
	}


	//------------------------------------------


	inline static void gotoxy(int x, int y) //inline 해당함수 호출부분 생략. 호출 전 data 영역에 메모리를 올려둔다. 빠른 호출 가능
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