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
{//�ʱ� ���� Goal������ ���ڸ� ������� �ʴ´�.

	m_IMG_NowMotion = IMG_OBJECT_GOAL;
	m_EndPositionCheck = false;
	m_bActiveCheck = false;

	m_Draw_X = _X; //�̰� Goal�� ��Ÿ���� ������ ���ش�.
	m_Draw_Y = _Y;

	//10M���� ������ ��밡 �� ��ġ�� �ִ� ��Ȳ���� ����
	if (GMMgr->Judgment_First_M_Value() == 10)
	{
		m_bActiveCheck = true;
		m_EndPositionCheck = true;
	}


	//Rect ����
	//top�� bottom�� ������ �ʴ´�.
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
	//ĳ���Ͱ� �ڷ� ���ڸ��� goal�� ��������. �ٽ� ������ ���� goal�� ���ڱ� ��Ÿ���� �� �ذ�
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance);// *10;

	//������ ����. (IMG �������� ��ȯ)
	//��� �̵��� ���� ����. Ư�� x��ǥ�� ������ ���
	if (m_Draw_X <= GOAL_IMG_ARRIVE_X) //�����ϱ� �������� GOAL_IMG_ARRIVE_X�� �� �۾ƾ� �Ѵ�.
	{
		m_Draw_X = GOAL_IMG_ARRIVE_X;
		m_EndPositionCheck = true;
	}
	else
		m_EndPositionCheck = false;

	//Rect ����
	SetRect();
}

void Goal::SetRect()
{
	//Draw Rect�� right ����
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + GOAL_IMG_W;
}