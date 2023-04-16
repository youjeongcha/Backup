#include "Goal.h"
#include "GameManager.h"

Goal::Goal()
{
	m_bActiveCheck = false;
	m_EndPositionCheck = false;
	//InitialSet();
}

Goal::~Goal()
{
}

void Goal::InitialSet(int _X, int _Y)
{//초기 세팅 Goal에서는 인자를 사용하지 않는다.

	m_IMG_NowMotion = IMG_OBJECT_GOAL;
	m_EndPositionCheck = false;
	m_bActiveCheck = false;

	m_Draw_X = _X; //이건 Goal이 나타날때 세팅을 해준다.
	m_Draw_Y = _Y;

	//10M에서 죽으면 골대가 제 위치에 있는 상황에서 시작
	if (GMMgr->Judgment_First_M_Value() == 10)
	{
		m_bActiveCheck = true;
		m_EndPositionCheck = true;
	}


	//Rect 세팅
	//top과 bottom은 변하지 않는다.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + GOAL_IMG_H;

	SetRect();
}

void Goal::Draw(HDC hdc)
{
	//if (m_bActiveCheck == true)
		BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, GOAL_IMG_W, GOAL_IMG_H);
}

void Goal::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{	
	//캐릭터가 뒤로 가자마자 goal이 없어지고. 다시 앞으로 가서 goal이 갑자기 나타나는 거 해결
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance);// *10;

	//앞으로 간다. (IMG 왼쪽으로 순환)
	//배경 이동이 끝이 난다. 특정 x좌표에 도착한 경우
	if (m_Draw_X <= GOAL_IMG_ARRIVE_X) //도착하기 전까지는 GOAL_IMG_ARRIVE_X가 더 작아야 한다.
	{
		m_Draw_X = GOAL_IMG_ARRIVE_X;
		m_EndPositionCheck = true;
	}
	else
		m_EndPositionCheck = false;

	//Rect 세팅
	SetRect();
}

void Goal::SetRect()
{
	//Draw Rect의 right 갱신
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + GOAL_IMG_W;
}