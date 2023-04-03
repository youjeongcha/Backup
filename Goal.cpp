#include "Goal.h"
#include "GameManager.h"

Goal::Goal()
{
	m_EndPositionCheck = false;

	//m_Rect[RECTTYPE_BITMAP].left = TRAVELDISTANCE_END - 20;
	//m_Rect[RECTTYPE_BITMAP].left = -999; //이건 Goal이 나타날때 세팅을 해준다.
	m_Rect[RECTTYPE_BITMAP].left = METER_END_SHOW_X + 100; //이건 Goal이 나타날때 세팅을 해준다.
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

void Goal::Update(float thisTurn_MoveDistance)
{	
	//캐릭터가 뒤로 가자마자 goal이 없어지고. 다시 앞으로 가서 goal이 갑자기 나타나는 거 해결
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Rect[RECTTYPE_BITMAP].left -= thisTurn_MoveDistance;
		//m_Rect[RECTTYPE_BITMAP].left -= deltaTime * SPEED_METER * thisTurn_MoveDistance;

	if (thisTurn_MoveDistance > 0)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		//특정 x좌표에 도착한 경우
		if (m_Rect[RECTTYPE_BITMAP].left <= GOAL_IMG_ARRIVE_X) //도착하기 전까지는 GOAL_IMG_ARRIVE_X가 더 작아야 한다.
		{
			m_Rect[RECTTYPE_BITMAP].left = GOAL_IMG_ARRIVE_X;
			m_EndPositionCheck = true;
		}
		else
			m_EndPositionCheck = false;
	}
	//else if (thisTurn_MoveDistance < 0)
	//{ //뒤로 간다. (IMG 오른쪽으로 순환)
	//	//m_EndPositionCheck = false;
	//}


	//Bump체크에 필요
	m_Rect[RECTTYPE_BITMAP].right = m_Rect[RECTTYPE_BITMAP].left + GOAL_IMG_W;
}
