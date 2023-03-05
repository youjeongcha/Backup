#include "MapDraw.h"
#include "Interface.h"

MapDraw::MapDraw()
{

}
MapDraw::~MapDraw()
{
}


void MapDraw::ErasePoint(int x, int y)
{//화살표 삭제
	gotoxy(x * 2, y);
	std::cout << "    ";
	return;
}
//void MapDraw::EraseWord(int strSize, int x, int y)
//{
//	gotoxy(x * 2, y);
//	for (int i = 0; i < strSize; i++)
//		std::cout << " ";
//	return;
//}
void MapDraw::DrawPoint(std::string str, int x, int y)
{
	gotoxy(x * 2, y);
	std::cout << str;
	return;
}
void MapDraw::DrawVerticalLine()
{
	int x = STAGEPRINT_STAIRS_X;

	for (int y = MAPSIZE_SART_Y + 1; y <= MAPSIZE_END_Y ; y++)
		DrawPoint("│", x, y);

	return;
}

void MapDraw::DrawMidText(std::string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	std::cout << str;
	return;
}
//void MapDraw::TextDraw(std::string str, int x, int y)
//{
//	gotoxy(x, y);
//	std::cout << str;
//}



//void MapDraw::SpcaeErase(int Start_x, int Start_y, int Width, int Height)
//{
//	for (int y = Start_y; y <= Height; y++)
//	{
//		//gotoxy(2, y);
//		for (int x = Start_x; x < Width - 1; x++)
//			DrawPoint("  ", x, y);
//	}
//}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			std::cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				std::cout << "─";
			std::cout << "┐";
		}
		else if (y == Height - 1)
		{
			std::cout << "└";
			for (int x = 1; x < Width - 1; x++)
				std::cout << "─";
			std::cout << "┘";
		}
		else
		{
			std::cout << "│";
			for (int x = 1; x < Width - 1; x++)
				std::cout << "  ";
			std::cout << "│";
		}
	}
	return;
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("▷", x, y);
	ORIGINAL
		while (1)
		{
			switch (getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}