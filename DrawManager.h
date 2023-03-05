#pragma once
#include"Mecro.h"

class DrawManager
{
public:
	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	static void DrawPanel(int Width, int Height)
	{//판 싹다 그리는 거
		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				if (x == 0 && y == 0)
					cout << "┌";
				else if (y == 0 && x == Width - 1)
					cout << "┐";
				else if (y == 0 && x > 0 && x < Width - 1)
					cout << "┬";
				else if (y == Height - 1 && x > 0 && x < Width - 1)
					cout << "┴";
				else if (x == 0 && y > 0 && y < Height - 1)
					cout << "├";
				else if (x == Width - 1 && y > 0 && y < Height - 1)
					cout << "┤";
				else if (x == 0 && y == Height - 1)
					cout << "└";
				else if (x == Width - 1 && y == Height - 1)
					cout << "┘";
				else
					cout << "┼";
			}
			cout << endl;
		}
	}

	static void DrawPoint(string str, int x, int y)
	{
		gotoxy(x * 2, y);
		cout << str;
	}

	static void DrawMidText(string str, int x, int y)
	{
		if (x > str.size() / 2)
			x -= str.size() / 2;
		gotoxy(x, y);
		cout << str;
	}

	static void ErasePoint(int x, int y)
	{
		gotoxy(x * 2, y);
		cout << "  ";
	}
	static void ErasePanel(int x, int y, int Width, int Height)
	{
		gotoxy(x * 2, y);
		if (x == 0 && y == 0)
			cout << "┌";
		else if (y == 0 && x == Width - 1)
			cout << "┐";
		else if (y == 0 && x > 0 && x < Width - 1)
			cout << "┬";
		else if (y == Height - 1 && x > 0 && x < Width - 1)
			cout << "┴";
		else if (x == 0 && y > 0 && y < Height - 1)
			cout << "├";
		else if (x == Width - 1 && y > 0 && y < Height - 1)
			cout << "┤";
		else if (x == 0 && y == Height - 1)
			cout << "└";
		else if (x == Width - 1 && y == Height - 1)
			cout << "┘";
		else
			cout << "┼";
	}

	static void BoxDraw(int Start_x, int Start_y, int Width, int Height)
	{
		Start_x -= Width;
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
	}

};