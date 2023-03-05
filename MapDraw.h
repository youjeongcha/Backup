#pragma once
#include"Mecro.h"

//멤버변수가 없다 > 클래스로 객체를 만들 생각이 없다.
//도구들을 집합시킨 유틸성 클래스
class MapDraw
{
public:
	static void BoxDraw(int Start_x, int Start_y, int Width, int Height)
	{
		for (int y = 0; y < Height; y++)
		{
			gotoxy(Start_x, Start_y + y);
			if (y == 0)
			{
				cout << "┌";
				for (int x = 1; x < Width - 1; x++)
					cout << "─";
				cout << "┐";
			}
			else if (y == Height - 1)
			{
				cout << "└";
				for (int x = 1; x < Width - 1; x++)
					cout << "─";
				cout << "┘";
			}
			else
			{
				cout << "│";
				for (int x = 1; x < Width - 1; x++)
					cout << "  ";
				cout << "│";
			}
		}
		return;
	}
	static void DrawPoint(string str, int x, int y)
	{//특수문자는 일반문자의 두배. 특수문자 기준으로 바꿔준다.
		gotoxy(x * 2, y);
		cout << str;
		return;
	}
	static void DrawMidText(string str, int x, int y)
	{//중간기준 출력 //중앙정렬
		if (x > str.size() / 2)
			x -= str.size() / 2;//반만큼 땡긴다.
		gotoxy(x, y);
		cout << str;
		return;
	}
	static void TextDraw(string str, int x, int y)
	{//좌측 기준 출력 //좌측정렬
		gotoxy(x, y);
		cout << str;
	}
	static void ErasePoint(int x, int y)
	{
		gotoxy(x * 2, y);
		cout << "  ";
		return;
	}
	MapDraw() {}
	static inline void gotoxy(int x, int y) //inline 해당함수 호출부분 생략. 호출 전에 미리 data 영역에 메모리를 올려둔다. 빠른 호출 가능
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~MapDraw() {}
};