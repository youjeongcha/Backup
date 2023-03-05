#include "Stone.h"

void Stone::SetPosition(int _ix, int _iy)
{
	m_ix = _ix;
	m_iy = _iy;
}
void Stone::SetPosition(int _ix, int _iy, string _strShape)
{
	m_ix = _ix;
	m_iy = _iy;
	m_strShape = _strShape;
}

void Stone::DrawUndoStone()
{
	if(m_ix != - 1 && m_iy != -1)
		DrawManager::DrawPoint("¡Ø", m_ix, m_iy);
}

void Stone::DrawStone()
{
	DrawManager::DrawPoint(m_strShape, m_ix, m_iy);
}
void Stone::EraseStone(int _iWidth, int _iHeight)
{
	DrawManager::ErasePanel(m_ix, m_iy,_iWidth,_iHeight);
}


bool Stone::Compare(Stone stone)
{
	if (m_ix != -1 && m_iy != -1 && m_ix == stone.m_ix && m_iy == stone.m_iy)
	{
		return true;
	}
	else return false;
}

bool Stone::Compare(int _ix, int _iy)
{

	if (m_ix != -1 && m_iy != -1 && m_ix == _ix && m_iy == _iy)
	{
		return true;
	}
	else return false;
}

void Stone::Disable(int _iWidth, int _iHeight,bool EraseStatus)
{ 
	if(m_ix != -1 && m_iy != -1 && EraseStatus)
		EraseStone(_iWidth, _iHeight);
	m_ix = -1; 
	m_iy = -1; 
}

Stone::Stone()
{
	m_ix = -1;
	m_iy = -1;
}


Stone::Stone(int _ix, int _iy, string _strShape)
{
	m_ix = _ix;
	m_iy = _iy;
	m_strShape = _strShape;
}

Stone::Stone(int _ix, int _iy)
{
	m_ix = _ix;
	m_iy = _iy;
}
Stone::~Stone()
{

}