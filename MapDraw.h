#pragma once
#include"Mecro.h"

#define ENTER 13
//#define BOXSECTOR_DRAW_X Start_x / GAP_3 * GAP_4;
//#define BOXSECTOR_DRAW_Y Start_y / GAP_3 * GAP_2;

enum MENU
{
	MENU_m = 'm',
	MENU_M = 'M',
	MENU_PLAYER = 1,
	MENU_MONSTER,
	MENU_SAVE,
	MENU_END,
	MENU_GAMEEXIT,
};
enum MENUPRINT
{
	MENUPRINT_START_X = 10,
	MENUPRINT_START_Y = 8
};
enum DIRECTION
{
	DIRECTION_UP = 'w',
	DIRECTION_BIG_UP = 'W',
	DIRECTION_DOWN = 's',
	DIRECTION_BIG_DOWN = 'S',
	DIRECTION_LEFT = 'a',
	DIRECTION_BIG_LEFT = 'A',
	DIRECTION_RIGHT = 'd',
	DIRECTION_BIG_RIGHT = 'D',
};

enum MAP
{
	MAP_START = 0,
	MAP_END_X = 40,
	MAP_END_Y = 24,
};

enum GAP
{ //padding gap�� �ٸ� ǥ��?
	GAP_1 = 1,
	GAP_2,
	GAP_3,
	GAP_4,
	GAP_5,
	GAP_6,
	GAP_7,
	GAP_8,
	GAP_9,
	GAP_10,
	GAP_11,
	GAP_12,
	GAP_13,
};



class MapDraw
{
public:
	static void BoxDraw(int Start_x, int Start_y, int Width, int Height);//�ڽ��� ���� ��ĭ �׸�
	static void BoxSectorDraw(int Start_x, int Start_y, int Width, int Height);//�ڽ� �ȿ� �� �׾��ִ�
	static void BoxErase(int Width, int Height); //�ڽ� ���ʸ� ����� �ڵ�

	static void DrawPoint(string str, int x, int y);
	static void DrawMidText(string str, int x, int y);
	static void TextDraw(string str, int x, int y);
	//static void Print(string _string); //
	static void ErasePoint(int x, int y);
	static int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	static int MenuSelectCursor_XY(int MenuLenX, int MenuLenY, int AddColX, int AddColY, int x, int y);
	//static void EraseBigBox

	//static void UnderInfo();
	//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����

	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};