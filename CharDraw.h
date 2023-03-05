#pragma once
#include"Mecro.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

class CharDraw
{
private:
	Position m_position;
public:
	//static Position m_position; //static�� ����. �׷��� ĳ���� ��ǥ�� ĳ���Ͱ� �������� ���ϰ� �ȴ�. >> ��� ĳ���Ͱ� ���� ��ǥ�� �ְ� �ȴ�. >> ��� �Լ��� ���� ���� �´�.
	void StartCharDraw(int Start_x, int Start_y, int Width, int Height);
	bool MoveObstacleCheck(int Start_x, int Start_y, int Width, int Height, char ch);
	void ErasePoint(int x, int y);
	void MoveCharDraw(int Start_x, int Start_y, int Width, int Height);
	inline void gotoxy(int x, int y);
};