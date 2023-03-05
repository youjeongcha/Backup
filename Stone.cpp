#include "Stone.h"



void Stone::SetPosition(int _ix, int _iy, string _strShape) {
	m_ix = _ix;
	m_iy = _iy;
	m_strShape = _strShape;
}

void Stone::DrawUndoStone()
{//무르기 돌 표시
	if(m_ix != - 1 && m_iy != -1) //조건식 왜?
		DrawManager::DrawPoint("※", m_ix, m_iy);
}

void Stone::DrawStone()
{//주의. 이런 형태로 돌 사용처 명확하게 
	DrawManager::DrawPoint(m_strShape, m_ix, m_iy);
}
void Stone::EraseStone(int _iWidth, int _iHeight)
{
	DrawManager::ErasePanel(m_ix, m_iy,_iWidth,_iHeight);
}


bool Stone::Compare(Stone stone) //자기 class 객체를 이용하는 것 가능
{//돌 둘 수 있는지 없는지 비교? //이쪽도 -1로 이용하는 돌인지 비활성화 돌인지 판단
	if (m_ix != -1 && m_iy != -1 && m_ix == stone.m_ix && m_iy == stone.m_iy)
	{
		return true;
	}
	else return false;
}

bool Stone::Compare(int _ix, int _iy)
{//좌표 비교

	if (m_ix != -1 && m_iy != -1 && m_ix == _ix && m_iy == _iy)
	{
		return true;
	}
	else return false;
}

void Stone::Disable(int _iWidth, int _iHeight,bool EraseStatus)
{ //disable은 돌을 비활성화 좌표상에 존재하지 않는 -1로
	if(m_ix != -1 && m_iy != -1 && EraseStatus) // == 없으면 EraseStatus가 true면 작동
		EraseStone(_iWidth, _iHeight);
	m_ix = -1; 
	m_iy = -1; 
}

Stone::Stone()
{
	m_ix = -1;
	m_iy = -1;
}

Stone::Stone(int _ix, int _iy)
{
	m_ix = _ix;
	m_iy = _iy;
}
Stone::~Stone()
{

}