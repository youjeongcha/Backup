#include "Goal.h"
#include "GameManager.h"

Goal::Goal()
{
	//InitialSet();
}

Goal::~Goal()
{
}

void Goal::InitialSet(IMG _IMG_X, int _X, int _Y)
{//초기 세팅 Goal에서는 인자를 사용하지 않는다.

	m_IMG_NowMotion = _IMG_X;
	m_EndPositionCheck = false;

	m_Draw_X = _X; //이건 Goal이 나타날때 세팅을 해준다.
	m_Draw_Y = _Y;

	m_Collider_Rect.left = m_Draw_X;
	m_Collider_Rect.top = m_Draw_Y;
	m_Collider_Rect.right = m_Collider_Rect.left + GOAL_IMG_W;
	m_Collider_Rect.bottom = m_Collider_Rect.top + GOAL_IMG_H;
}

void Goal::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, GOAL_IMG_W, GOAL_IMG_H);
}

void Goal::Update(float total_MoveDistance, float _Prev_MoveDistance)
{	
	//캐릭터가 뒤로 가자마자 goal이 없어지고. 다시 앞으로 가서 goal이 갑자기 나타나는 거 해결
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) *10;
		//m_Rect[RECTTYPE_BITMAP].left -= deltaTime * SPEED_METER * thisTurn_MoveDistance;


	//앞으로 간다. (IMG 왼쪽으로 순환)
	//배경 이동이 끝이 난다. 특정 x좌표에 도착한 경우
	if (m_Draw_X <= GOAL_IMG_ARRIVE_X) //도착하기 전까지는 GOAL_IMG_ARRIVE_X가 더 작아야 한다.
	{
		m_Draw_X = GOAL_IMG_ARRIVE_X;
		m_EndPositionCheck = true;
	}
	else
		m_EndPositionCheck = false;

	//Draw Rect의 right 갱신
	m_Collider_Rect.left = m_Draw_X;
	m_Collider_Rect.top = m_Draw_Y;
	m_Collider_Rect.right = m_Collider_Rect.left + GOAL_IMG_W;
	m_Collider_Rect.bottom = m_Collider_Rect.top + GOAL_IMG_H;
	//m_Rect[RECT_BITMAP].right = m_Rect[RECT_BITMAP].left + GOAL_IMG_W;
	//Bump체크에 필요
	//m_Rect[RECT_COLLIDER] = m_Rect[RECT_BITMAP];
}

//RECT Goal::Get_Rect()
//{
//	return m_Rect[RECTTYPE_BUMP];
//}
