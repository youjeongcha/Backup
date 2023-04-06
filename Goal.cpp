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
	//ĳ���Ͱ� �ڷ� ���ڸ��� goal�� ��������. �ٽ� ������ ���� goal�� ���ڱ� ��Ÿ���� �� �ذ�
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) *10;
		//m_Rect[RECTTYPE_BITMAP].left -= deltaTime * SPEED_METER * thisTurn_MoveDistance;


	//������ ����. (IMG �������� ��ȯ)
	//��� �̵��� ���� ����. Ư�� x��ǥ�� ������ ���
	if (m_Draw_X <= GOAL_IMG_ARRIVE_X) //�����ϱ� �������� GOAL_IMG_ARRIVE_X�� �� �۾ƾ� �Ѵ�.
	{
		m_Draw_X = GOAL_IMG_ARRIVE_X;
		m_EndPositionCheck = true;
	}
	else
		m_EndPositionCheck = false;

	//Draw Rect�� right ����
	m_Collider_Rect.left = m_Draw_X;
	m_Collider_Rect.top = m_Draw_Y;
	m_Collider_Rect.right = m_Collider_Rect.left + GOAL_IMG_W;
	m_Collider_Rect.bottom = m_Collider_Rect.top + GOAL_IMG_H;
	//m_Rect[RECT_BITMAP].right = m_Rect[RECT_BITMAP].left + GOAL_IMG_W;
	//Bumpüũ�� �ʿ�
	//m_Rect[RECT_COLLIDER] = m_Rect[RECT_BITMAP];
}

//RECT Goal::Get_Rect()
//{
//	return m_Rect[RECTTYPE_BUMP];
//}
