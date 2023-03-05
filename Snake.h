#pragma once
#include "Mecro.h"
#include "Block.h"


#define SNAKE_SPEED_DEFAULT 800
#define SNAKE_FASTER 50


enum DIRECTION
{
	LEFT = 97,
	RIGHT = 100,
	UP = 119,
	DOWN = 115,

	CAPITAL_LEFT = 65,
	CAPITAL_RIGHT = 68,
	CAPITAL_UP = 87,
	CAPITAL_DOWN = 83
};

class Snake
{//static�� ��������. ���������� �ִ��� ���°� ����.
	//���� ������ ��������ų� ����� ���ܾ� �ϴ� ��Ȳ�� ���� ���� �����Ƿ� > ���� ������Ʈ�� manager���� ��������� �ϳ��� �����ؼ� ����ϵ���
public:
	static XY m_InputXY; //�Ӹ��� ����������� �� ĭ �����̴��� ���
	static XY m_beforeXY; //���� block�� xy��ǥ�� �����صδ� ����
	static list<Block> snakeList;
	static bool m_inputCheck; //�ߺ� ���� �Է� �Ұ�. <- �ϰ� �ִ� �߿� [��, ->] ������ ������ �ݴ� ù��° �Է� �����ϰ� �ι�°, �� �ݴ�� ���°� ����

	static void SnakeCreate(BlockCheck snakePart);

	static void SnakeInput();
	static void InputReset();

	static bool SankeMoveLimit(XY checkXY, int reverseX, int reverseY);
	static void SnakeMove();

	Snake();
	~Snake();
};

