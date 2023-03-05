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
	//static Position m_position; //static은 전역. 그래서 캐릭터 좌표를 캐릭터가 관리하지 못하게 된다. >> 모든 캐릭터가 같은 좌표에 있게 된다. >> 멤버 함수로 쓰는 것이 맞다.
	void StartCharDraw(int Start_x, int Start_y, int Width, int Height);
	bool MoveObstacleCheck(int Start_x, int Start_y, int Width, int Height, char ch);
	void ErasePoint(int x, int y);
	void MoveCharDraw(int Start_x, int Start_y, int Width, int Height);
	inline void gotoxy(int x, int y);
};