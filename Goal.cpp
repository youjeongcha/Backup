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
{//�ʱ� ���� Goal������ ���ڸ� ������� �ʴ´�.

	m_IMG_NowMotion = _IMG_X;
	m_EndPositionCheck = false;

	m_Draw_X = _X; //�̰� Goal�� ��Ÿ���� ������ ���ش�.
	m_Draw_Y = _Y;


	//Rect ����
	//top�� bottom�� ������ �ʴ´�.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + GOAL_IMG_H;

	SetRect();
}

void Goal::Draw(HDC hdc)
{
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