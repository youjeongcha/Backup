#include "Goal.h"
#include "GameManager.h"

Goal::Goal()
{
	m_EndPositionCheck = false;

	//m_Rect[RECTTYPE_BITMAP].left = TRAVELDISTANCE_END - 20;
	//m_Rect[RECTTYPE_BITMAP].left = -999; //�̰� Goal�� ��Ÿ���� ������ ���ش�.
	m_Rect[RECTTYPE_BITMAP].left = METER_END_SHOW_X + 100; //�̰� Goal�� ��Ÿ���� ������ ���ش�.
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
	//ĳ���Ͱ� �ڷ� ���ڸ��� goal�� ��������. �ٽ� ������ ���� goal�� ���ڱ� ��Ÿ���� �� �ذ�
	if (m_EndPositionCheck == false)// || (thisTurn_MoveDistance < 0 && m_ActiveCheck == true))
		m_Rect[RECTTYPE_BITMAP].left -= thisTurn_MoveDistance;
		//m_Rect[RECTTYPE_BITMAP].left -= deltaTime * SPEED_METER * thisTurn_MoveDistance;

	if (thisTurn_MoveDistance > 0)
	{ //������ ����. (IMG �������� ��ȯ)
		//Ư�� x��ǥ�� ������ ���
		if (m_Rect[RECTTYPE_BITMAP].left <= GOAL_IMG_ARRIVE_X) //�����ϱ� �������� GOAL_IMG_ARRIVE_X�� �� �۾ƾ� �Ѵ�.
		{
			m_Rect[RECTTYPE_BITMAP].left = GOAL_IMG_ARRIVE_X;
			m_EndPositionCheck = true;
		}
		else
			m_EndPositionCheck = false;
	}
	//else if (thisTurn_MoveDistance < 0)
	//{ //�ڷ� ����. (IMG ���������� ��ȯ)
	//	//m_EndPositionCheck = false;
	//}


	//Bumpüũ�� �ʿ�
	m_Rect[RECTTYPE_BITMAP].right = m_Rect[RECTTYPE_BITMAP].left + GOAL_IMG_W;
}
