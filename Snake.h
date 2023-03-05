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
{//static은 전역변수. 전역벼누는 최대한 없는게 좋다.
	//뱀이 여러개 만들어지거나 목숨이 생겨야 하는 상황이 있을 수도 있으므로 > 다음 프로젝트는 manager에서 멤버변수로 하나만 생성해서 사용하도록
public:
	static XY m_InputXY; //머리가 어느방향으로 한 칸 움직이는지 기록
	static XY m_beforeXY; //앞전 block의 xy좌표를 유지해두는 역할
	static list<Block> snakeList;
	static bool m_inputCheck; //중복 방향 입력 불가. <- 하고 있던 중에 [위, ->] 빠르게 눌러서 반대 첫번째 입력 무시하고 두번째, 즉 반대로 가는거 방지

	static void SnakeCreate(BlockCheck snakePart);

	static void SnakeInput();
	static void InputReset();

	static bool SankeMoveLimit(XY checkXY, int reverseX, int reverseY);
	static void SnakeMove();

	Snake();
	~Snake();
};

