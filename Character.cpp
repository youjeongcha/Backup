#include "Character.h"



Character::Character()
{
	m_strShape = "¢»";
}


void Character::SetPosition(Position _position, Size _mapSize)
{
	m_mapSize.m_iLeft = _position.m_ix;
	m_mapSize.m_iUp = _position.m_iy;
	m_mapSize.m_iRight = _position.m_ix + _mapSize.m_iWidth * 2;
	m_mapSize.m_iDown = _position.m_iy + _mapSize.m_iHeight;
	m_position.m_ix = _position.m_ix + _mapSize.m_iWidth - 1;
	m_position.m_iy = _position.m_iy + _mapSize.m_iHeight / 2;
}



void Character::Move()
{
	while(1)
	{
		char ch = getch();
		bool bMoveStatus = false;
		Position prevPosition = m_position;
		switch(ch)
		{
			case DIRECTION_LEFT:
				if (m_position.m_ix - 1 >= m_mapSize.m_iLeft + 2)
				{
					m_position.m_ix--;
					bMoveStatus = true;
				}
				break;
			case DIRECTION_RIGHT:
				if (m_position.m_ix + 1 <= m_mapSize.m_iRight - 4)
				{
					m_position.m_ix++;
					bMoveStatus = true;
				}
				break;
			case DIRECTION_UP:
				if (m_position.m_iy - 1 > m_mapSize.m_iUp)
				{
					m_position.m_iy--;
					bMoveStatus = true;
				}
				break;
			case DIRECTION_DOWN:
				if (m_position.m_iy + 1 < m_mapSize.m_iDown - 1)
				{
					m_position.m_iy++;
					bMoveStatus = true;
				}
				break;
		}
		if (bMoveStatus)
		{
			MapDraw::TextDraw("  ",prevPosition.m_ix, prevPosition.m_iy);
			Draw();
		}
	}
}


void Character::Draw()
{
	MapDraw::TextDraw(m_strShape, m_position.m_ix, m_position.m_iy);
}


Character::~Character()
{
}
