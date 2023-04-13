#include "FirRing_B.h"
#include "GameManager.h"

FirRing_B::FirRing_B()
{
	//m_UsingCheck = true;
	m_IMG_NowMotion == IMG_OBJECT_RING_LEFT_1;
	m_IMG_NowMotion_R == IMG_OBJECT_RING_RIGHT_1;
	m_AllotScore = SCORE_100;
}

FirRing_B::~FirRing_B()
{
}


void FirRing_B::InitialSet(int _X, int _Y)
{
	m_bActiveCheck = true;
	m_IMG_NowMotion = IMG_OBJECT_RING_LEFT_1;
	m_IMG_NowMotion_R = IMG_OBJECT_RING_RIGHT_1;

	m_Draw_X = _X;
	m_Draw_Y = _Y;

	//Rect ����
	SetRect();
}

void FirRing_B::Draw(HDC hdc)
{
	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRRING_W, FIRRING_H);
	}
}

void FirRing_B::Draw_OnCharacter(HDC hdc)
{
	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion_R)->DrawTransparent(hdc, m_Draw_X + FIRRING_W, m_Draw_Y, FIRRING_W, FIRRING_H);
	}
}

void FirRing_B::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{
	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_UsingCheck == true)
	{
		//�ִϸ��̼�
		Animation(deltaTime);

		//-----------------------

		//�Ҹ� �̵�
		//�� �ð��� ���� �������� �ϴ� �� �ִٸ� deltaTime�� �����ش�.�� 
		//�ð��� ��ǥ�� �̵��ϴ� �� //m_Draw_X -= 5; �ϸ� �ȴ�.
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) + -MOVE_SPEED_FRIERING_B * deltaTime;

		//Goal�� Ư�� ��ǥ�� ���� ��ȯ�� �����.
		//if (GMMgr->Get_GoalEndPositionCheck() == false)
		{
			//m_UsingCheck = true; //�� ���� ����ٰ� �ٽ� �����ϴ� ��츦 ����

			if (m_Draw_X <= START_SHOW_X) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
			{ //������ ����. (IMG �������� ��ȯ)
				m_bActiveCheck = true;
				m_Draw_X += METER_ACROSS_ONE; //�̹��� �ϳ� �ǳʼ� ���
			}
			else if (m_Draw_X >= END_SHOW_X)
			{ //�ڷ� ����. (IMG ���������� ��ȯ)
				m_Draw_X -= METER_ACROSS_ONE;
			}
		}
		//else //Goal�� Ư�� ��ǥ�� ���� ��ȯ�� �����.
		//{
		//	if (m_Draw_X <= START_SHOW_X) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
		//	{ //������ ����. (IMG �������� ��ȯ)
		//		m_UsingCheck = false;
		//	}
		//}

		SetRect(); //Rect ����
	}
}

void FirRing_B::Animation(float deltaTime)
{ //�̱۰Ÿ��� �ִϸ��̼�
	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_UsingCheck == true)
	{
		if (m_AnimationTime >= ANI_SPEED_FIRE)
		{
			m_AnimationTime = 0;

			//���� ��
			if (m_IMG_NowMotion == IMG_OBJECT_RING_LEFT_1)
				m_IMG_NowMotion = IMG_OBJECT_RING_LEFT_2;
			else
				m_IMG_NowMotion = IMG_OBJECT_RING_LEFT_1;

			//������ ��
			if (m_IMG_NowMotion_R == IMG_OBJECT_RING_RIGHT_1)
				m_IMG_NowMotion_R = IMG_OBJECT_RING_RIGHT_2;
			else
				m_IMG_NowMotion_R = IMG_OBJECT_RING_RIGHT_1;
		}

		m_AnimationTime += deltaTime;
	}
}

void FirRing_B::SetRect()
{ //Rect ����


	//�ε���
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + FIRRING_W;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRRING_COLLIDER_W;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + FIRRING_H;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRRING_COLLIDER_H;

	//����
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //ĳ���� �ִ� ���� ���̱���
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}