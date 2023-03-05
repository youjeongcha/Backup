#include "Snake.h"

Snake::Snake()
{
	m_InputXY.x = 0;
	m_InputXY.y = 0;
	m_inputCheck = false;
}

//static 변수는 선언을 .cpp에서 해야 한다.
XY Snake::m_InputXY;
XY Snake::m_beforeXY;
list<Block> Snake::snakeList;
bool Snake::m_inputCheck;

//수정
void Snake::SnakeCreate(BlockCheck snakePart)
{
	Block block = block.NewBlock();

	if (snakePart == Snake_Head)
	{
		block.SetXY(PATERN_APPOINT, WIDTH / 2 * 2, HEIGHT / 2 - 1); //추후 수정 25 * 2, 14
		block.DrawBlock(block.CheckBlock(BlockCheck::Snake_Head));
	}
	else if (snakePart == Snake_Body)
	{
		block.SetXY(PATERN_APPOINT, m_beforeXY.x, m_beforeXY.y);
		block.DrawBlock(block.CheckBlock(BlockCheck::Snake_Body));
	}

	snakeList.push_back(block);
}

void Snake::InputReset()
{
	m_InputXY.x = 0;
	m_InputXY.y = 0;
}

void Snake::SnakeInput()
{
	if (kbhit()) //키보드 입력을 받으면 1, 받지 않으면 0
	{
		char ch = getch();

		if (m_inputCheck == false) //ture면 현재 입력값이 존재하는것. false면 현재 입력값이 존재하지 않는 것
		{
			m_inputCheck = true;

			switch (ch)
			{//xy구조체 만들어서. 그만큼 플러스 마이너스 값 
			case DIRECTION::LEFT:
			case DIRECTION::CAPITAL_LEFT:
				if (SankeMoveLimit(m_InputXY, 1, 0)) //SankeMoveLimit가 false면 현재 이동 방향과 반대 방향 > 방향 바뀌지 않는다.
				{
					m_InputXY.x = -1;
					m_InputXY.y = 0;
				}
				break;

			case DIRECTION::RIGHT:
			case  DIRECTION::CAPITAL_RIGHT:
				if (SankeMoveLimit(m_InputXY, -1, 0))
				{
					m_InputXY.x = 1;
					m_InputXY.y = 0;
				}
				break;

			case DIRECTION::UP:
			case DIRECTION::CAPITAL_UP:
				if (SankeMoveLimit(m_InputXY, 0, 1))
				{
					m_InputXY.x = 0;
					m_InputXY.y = -1;
				}
				break;

			case DIRECTION::DOWN:
			case DIRECTION::CAPITAL_DOWN:
				if (SankeMoveLimit(m_InputXY, 0, -1))
				{
					m_InputXY.x = 0;
					m_InputXY.y = 1;
				}
				break;
			}
		}
	}
}

bool Snake::SankeMoveLimit(XY presentXY, int reverseX, int reverseY)
{//현재 가고 있는 방향과 반대이면 움직임X :: false
	if ((presentXY.x == reverseX) && (presentXY.y == reverseY)) //현재 가고 있는 방향과 반대이면 움직임X
		return false;
	else
		return true;
}

void Snake::SnakeMove()
{
	//XY m_beforeXY;	//앞전 block의 xy좌표를 유지해두는 역할

	for (list<Block>::iterator iter = snakeList.begin(); iter != snakeList.end(); iter++)
	{

		if (iter == snakeList.begin()) //머리만 방향따라 곧바로 이동
		{
			iter->EarseBlock();
			m_beforeXY = iter->GetXY(); //block의 현재 좌표 유지해서 다음 블록에 넘겨주기 위해
			iter->MoveXY(m_InputXY.x, m_InputXY.y); //방향키대로 이동
			iter->DrawBlock(iter->CheckBlock(BlockCheck::Snake_Head));
		}
		else //몸통들은 앞 block을 따라 이동
		{
			XY tmpXY;

			//좌표 이동
			tmpXY = iter->GetXY();
			iter->EarseBlock();

			iter->SetXY(PATERN_APPOINT, m_beforeXY.x, m_beforeXY.y); //앞 block 따라가기
			iter->DrawBlock(iter->CheckBlock(BlockCheck::Snake_Body));

			m_beforeXY = tmpXY;
		}
	}
	m_inputCheck = false;
}

Snake::~Snake() { }