//하나의 블럭을 만들 수 있게한다
//생성(그리기), 지우기, 충돌확인
#pragma once
#include "Mecro.h"

typedef struct BlockShape
{
	string obstacle;
	string food;
	string snakeHead;
	string snakeBody;
};

static enum BlockCheck
{// 필요한지?
	Obstacle,
	Food,
	Snake_Head,
	Snake_Body
};

class Block
{
private:
	int m_X;
	int m_Y;
	//string m_Snake_Head;
	//string m_Snake_Body;
	//string m_Food;
	//string m_Obstacle;
public:
	Block NewBlock();
	XY GetXY();
	void MoveXY(int _X, int _Y);
	void SetXY(PATERN patern, int _X, int _Y);

	static string CheckBlock(BlockCheck blockCheck); //return 값으로 받아서 DrawBlock에서 그림. //사용할 블럭이 무엇인지 체크

	void DrawBlock(string block);
	void EarseBlock(); //콘솔 창만 지우기

	Block();
	~Block();
};