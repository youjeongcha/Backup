#include "Snake.h"

Snake::Snake()
{
	m_InputXY.x = 0;
	m_InputXY.y = 0;
	m_inputCheck = false;
}

//static ������ ������ .cpp���� �ؾ� �Ѵ�.
XY Snake::m_InputXY;
XY Snake::m_beforeXY;
list<Block> Snake::snakeList;
bool Snake::m_inputCheck;

//����
void Snake::SnakeCreate(BlockCheck snakePart)
{
	Block block = block.NewBlock();

	if (snakePart == Snake_Head)
	{
		block.SetXY(PATERN_APPOINT, WIDTH / 2 * 2, HEIGHT / 2 - 1); //���� ���� 25 * 2, 14
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
	if (kbhit()) //Ű���� �Է��� ������ 1, ���� ������ 0
	{
		char ch = getch();

		if (m_inputCheck == false) //ture�� ���� �Է°��� �����ϴ°�. false�� ���� �Է°��� �������� �ʴ� ��
		{
			m_inputCheck = true;

			switch (ch)
			{//xy����ü ����. �׸�ŭ �÷��� ���̳ʽ� �� 
			case DIRECTION::LEFT:
			case DIRECTION::CAPITAL_LEFT:
				if (SankeMoveLimit(m_InputXY, 1, 0)) //SankeMoveLimit�� false�� ���� �̵� ����� �ݴ� ���� > ���� �ٲ��� �ʴ´�.
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
{//���� ���� �ִ� ����� �ݴ��̸� ������X :: false
	if ((presentXY.x == reverseX) && (presentXY.y == reverseY)) //���� ���� �ִ� ����� �ݴ��̸� ������X
		return false;
	else
		return true;
}

void Snake::SnakeMove()
{
	//XY m_beforeXY;	//���� block�� xy��ǥ�� �����صδ� ����

	for (list<Block>::iterator iter = snakeList.begin(); iter != snakeList.end(); iter++)
	{

		if (iter == snakeList.begin()) //�Ӹ��� ������� ��ٷ� �̵�
		{
			iter->EarseBlock();
			m_beforeXY = iter->GetXY(); //block�� ���� ��ǥ �����ؼ� ���� ��Ͽ� �Ѱ��ֱ� ����
			iter->MoveXY(m_InputXY.x, m_InputXY.y); //����Ű��� �̵�
			iter->DrawBlock(iter->CheckBlock(BlockCheck::Snake_Head));
		}
		else //������� �� block�� ���� �̵�
		{
			XY tmpXY;

			//��ǥ �̵�
			tmpXY = iter->GetXY();
			iter->EarseBlock();

			iter->SetXY(PATERN_APPOINT, m_beforeXY.x, m_beforeXY.y); //�� block ���󰡱�
			iter->DrawBlock(iter->CheckBlock(BlockCheck::Snake_Body));

			m_beforeXY = tmpXY;
		}
	}
	m_inputCheck = false;
}

Snake::~Snake() { }