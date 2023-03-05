#include "Block.h"
#include "Manager.h"

Block::Block()
{
	//m_Obstacle = "▦";
	//m_Food = "♥";
	//m_Snake_Head = "⊙";
	//m_Snake_Body = "○";
}

Block Block::NewBlock()
{
	Block tmpBlock;
	return tmpBlock;
}

XY Block::GetXY()
{
	XY xy;
	xy.x = m_X;
	xy.y = m_Y;

	return xy;
}

void Block::MoveXY(int _X, int _Y)
{//Move는 Set과 달리 += 기존 XY를 기반으로 +1 -1 이동
	m_X += _X * 2;
	m_Y += _Y;
}

void Block::SetXY(PATERN patern, int _X, int _Y)
{
	if (patern == PATERN_APPOINT)
	{
		m_X = _X;
		m_Y = _Y;
	}
	else if (patern == PATERN_RANDOM)
	{
		m_X = (rand() % (WIDTH - 2) * 2) + 2; //허용범위 2~98 //0~48 * 2 + 2
		m_Y = rand() % (HEIGHT - 2) + 1;
	}
}

string Block::CheckBlock(BlockCheck blockCheck)
{
	switch (blockCheck)
	{
	case Obstacle:
		return "▦";
	case Food:
		return "♥";
	case Snake_Head:
		return "⊙";
	case Snake_Body:
		return "○";
	}

	return ""; //break하면 쓰레기값이 들어간다. 빈문자열이라도 출력되도록 해야 함.(특히 다른 언어)
}

void Block::DrawBlock(string block)
{
	gotoxy(m_X, m_Y);
	cout << block;
}

void Block::EarseBlock()
{
	gotoxy(m_X, m_Y);
	cout << "  ";
}


Block::~Block() {}