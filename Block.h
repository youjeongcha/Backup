//�ϳ��� ���� ���� �� �ְ��Ѵ�
//����(�׸���), �����, �浹Ȯ��
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
{// �ʿ�����?
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

	static string CheckBlock(BlockCheck blockCheck); //return ������ �޾Ƽ� DrawBlock���� �׸�. //����� ���� �������� üũ

	void DrawBlock(string block);
	void EarseBlock(); //�ܼ� â�� �����

	Block();
	~Block();
};