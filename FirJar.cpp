#include "FirJar.h"
#include "GameManager.h"

FirJar::FirJar()
{
	m_IMG_NowMotion = IMG_OBJECT_POT_1;


}

FirJar::~FirJar()
{
}

void FirJar::InitialSet(int _X, int _Y)
{
	m_IMG_NowMotion = IMG_OBJECT_POT_1;

	m_Draw_X = _X;
	m_Draw_Y = _Y;

	//Rect ����
	SetRect();
}

void FirJar::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRJAR_W, FIRJAR_H);
}

void FirJar::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{
	//�ִϸ��̼�
	Animation(deltaTime);

	//-----------------------

	//��� �̵�
	m_Draw_X += (_Prev_MoveDistance - total_MoveDistance);// *10;

	if (m_Draw_X <= START_SHOW_X) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
	{ //������ ����. (IMG �������� ��ȯ)
		m_Draw_X += METER_ACROSS_ONE; //�̹��� �ϳ� �ǳʼ� ���
	}
	else if (m_Draw_X >= END_SHOW_X)
	{ //�ڷ� ����. (IMG ���������� ��ȯ)
		m_Draw_X -= METER_ACROSS_ONE;
	}

	SetRect(); //Rect ����
}

void FirJar::Animation(float deltaTime)
{ //�̱۰Ÿ��� �ִϸ��̼�

	if (m_AnimationTime >= ANI_SPEED_FIRE)
	{
		m_AnimationTime = 0;
		
		if (m_IMG_NowMotion == IMG_OBJECT_POT_1)
			m_IMG_NowMotion = IMG_OBJECT_POT_2;
		else
			m_IMG_NowMotion = IMG_OBJECT_POT_1;
	}

	m_AnimationTime += deltaTime;
}

void FirJar::SetRect()
{//Rect ����
	
	//�ε���
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + BUMP_RECT_GAP;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRJAR_COLLIDER_W;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + BUMP_RECT_GAP;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRJAR_COLLIDER_H;

	//����
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //ĳ���� �ִ� ���� ���̱���
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}
