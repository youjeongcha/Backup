#include "MapDraw.h"

void MapDraw::DrawPoint(std::string str, int x, int y)
{
	gotoxy(x * 2, y);
	std::cout << str;
	return;
}