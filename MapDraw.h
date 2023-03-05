#pragma once
#include"Mecro.h"

#define UP 'w'
#define DOWN 's'
#define ENTER 13

class MapDraw
{
public:
	static void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	//static void SpcaeErase(int Start_x, int Start_y, int Width, int Height);
	static void DrawPoint(std::string str, int x, int y);
	//게임 진행, 마법사 창 세로선 그리기
	static void DrawVerticalLine();
	static void DrawMidText(std::string str, int x, int y);
	//static void TextDraw(std::string str, int x, int y);
	//화살표 삭제
	static void ErasePoint(int x, int y);
	//단어 "" 지우기
	//static void EraseWord(int strSize, int x, int y);
	static int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	MapDraw();
	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~MapDraw();
};

