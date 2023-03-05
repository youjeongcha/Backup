#pragma once
#include<iostream>
#include<string>
#include<conio.h>//getch()이용
#include<Windows.h>
using namespace std;

#define MAPMAX 20


enum Game
{
	OMOK,
	OTHELLO
};

enum CHARATER
{
	BLACK,
	WHITE
};

enum CONTINUE_CHECK
{
	NEW,
	CONTINUE
};

enum DIRECTION
{
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's',

	BACK = 'n',
	ENTER = '\r',
	ESC = '\x1b',

	WIN = 1,
	YET = 0
};

//////////////////////////// 어디에 사용?
enum XY
{
	X,
	Y
};

struct Position
{
	int m_ix;
	int m_iy;
};

//////////////////////////// 개선 가능할 거 같은데 어디 사용?
struct Rectingle
{//차이점
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