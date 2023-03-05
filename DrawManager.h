#pragma once
#include"Mecro.h"

class DrawManager
{
public:
	//static �Լ� ����ü�� ������. �ش� �Լ��� ��ü�ν��� �ǹ̰� ���� ������ static���� ����ϴ� ���� �´�.

	void static BoxDraw(int Start_x, int Start_y, int Width, int Height)
	{
		for (int y = 0; y < Height; y++)
		{
			gotoxy(Start_x, Start_y + y);
			if (y == 0)
			{
				cout << "��";
				for (int x = 1; x < Width - 1; x++)
					cout << "��";
				cout << "��";
			}
			else if (y == Height - 1)
			{
				cout << "��";
				for (int x = 1; x < Width - 1; x++)
					cout << "��";
				cout << "��";
			}
			else
			{
				cout << "��";
				for (int x = 1; x < Width - 1; x++)
					cout << "��";
				cout << "��";
			}
		}
		return;
	}

	//------------------------------------------

	string static MapDraw(int m_x, int m_y)
	{//static�� static���� ���� ����
		if (m_y == 0)
			return MapDrawPart(m_x, "��", "��", "��");
		else if (m_y == MAPMAX - 1)
			return MapDrawPart(m_x, "��", "��", "��");
		else
			return MapDrawPart(m_x, "��", "��", "��");
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


	inline static void gotoxy(int x, int y) //inline �ش��Լ� ȣ��κ� ����. ȣ�� �� data ������ �޸𸮸� �÷��д�. ���� ȣ�� ����
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	inline static void DrawPoint(string str, int x, int y)
	{//Ư�����ڴ� �Ϲݹ����� �ι�. Ư������ �������� �ٲ��ش�.
		gotoxy(x * 2, y);
		cout << str;
		return;
	}
	inline static void DrawMidText(string str, int x, int y)
	{//�߰����� ��� //�߾�����
		if (x > str.size() / 2)
			x -= str.size() / 2;//�ݸ�ŭ �����.
		gotoxy(x, y);
		cout << str;
		return;
	}
	inline static void TextDraw(string str, int x, int y)
	{//���� ���� ��� //��������
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