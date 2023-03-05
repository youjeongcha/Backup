#pragma once
#include<iostream>
#include<string>
#include<conio.h>//getch()�̿�
#include<iomanip>//cout�� ���Ĺ��� ����Ҷ�(�Ű� �� �ᵵ ��)
#include<Windows.h>
using namespace std;

#define MAPMAX 20


struct Position
{
	int m_ix;
	int m_iy;
};

struct Rectingle
{//������
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
	//static �Լ� ����ü�� ������. �ش� �Լ��� ��ü�ν��� �ǹ̰� ���� ������ static���� ����ϴ� ���� �´�.
	inline static void gotoxy(int x, int y) //inline �ش��Լ� ȣ��κ� ����. ȣ�� ���� �̸� data ������ �޸𸮸� �÷��д�. ���� ȣ�� ����
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
