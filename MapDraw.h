#pragma once
#include "Mecro.h"

class MapDraw
{
public:
	static void DrawPoint(std::string str, int x, int y);
	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

