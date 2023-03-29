#include "Goal.h"
#include "GameManager.h"

Goal::Goal()
{
	m_EndCheck = false;

	m_Rect[RECTTYPE_BITMAP].left = TRAVELDISTANCE_END - 20;
	m_Rect[RECTTYPE_BITMAP].top = IMG_CHARACTER_Y + 20;
	m_Rect[RECTTYPE_BITMAP].right = m_Rect[RECTTYPE_BITMAP].left + GOAL_IMG_W;
	m_Rect[RECTTYPE_BITMAP].bottom = m_Rect[RECTTYPE_BITMAP].top + GOAL_IMG_H;

	m_Rect[RECTTYPE_BUMP].left = m_Rect[RECTTYPE_BITMAP].left;
	m_Rect[RECTTYPE_BUMP].top = m_Rect[RECTTYPE_BITMAP].top;
	m_Rect[RECTTYPE_BUMP].right = m_Rect[RECTTYPE_BITMAP].right;
	m_Rect[RECTTYPE_BUMP].bottom = m_Rect[RECTTYPE_BITMAP].bottom;
}

Goal::~Goal()
{
}

void Goal::Draw(HDC hdc)
{
	BitMapMgr->GetImage(IMG_OBJECT_GOAL)->DrawTransparent(hdc, m_Rect[RECTTYPE_BITMAP].left, m_Rect[RECTTYPE_BITMAP].top, GOAL_IMG_W, GOAL_IMG_H);
}

void Goal::Update(float deltaTime, float thisTurn_MoveDistance)
{
	
	m_Rect[RECTTYPE_BITMAP].left -= deltaTime * SPEED_METER * thisTurn_MoveDistance;

	if (thisTurn_MoveDistance > 0)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		//특정 x좌표에 도착한 경우
		if (m_Rect[RECTTYPE_BITMAP].left <= GOAL_IMG_ARRIVE_X)
		{
			m_Rect[RECTTYPE_BITMAP].left = GOAL_IMG_ARRIVE_X;
			//m_EndCheck = true;
		}
		//else
			//m_EndCheck = false;
	}
	else if (thisTurn_MoveDistance < 0)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)
		//m_EndCheck = false;
	}


	//Bump체크에 필요
	m_Rect[RECTTYPE_BITMAP].right = m_Rect[RECTTYPE_BITMAP].left + GOAL_IMG_W;
}
