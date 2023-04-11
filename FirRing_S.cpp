#include "FirRing_S.h"
#include "GameManager.h"

FirRing_S::FirRing_S()
{
	m_IMG_Cash = IMG_OBJECT_CASH;
	m_UsingCheck = false;
}

FirRing_S::~FirRing_S()
{
}

void FirRing_S::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{
	if (m_UsingCheck == true)
	{
		//�ִϸ��̼�
		Animation(deltaTime);

		//-----------------------

		//�Ҹ� �̵�
		//�� �ð��� ���� �������� �ϴ� �� �ִٸ� deltaTime�� �����ش�.�� 
		//�ð��� ��ǥ�� �̵��ϴ� �� //m_Draw_X -= 5; �ϸ� �ȴ�.
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) + -MOVE_SPEED_FRIE * deltaTime;

		if (m_Draw_X <= START_SHOW_X) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
		{ //������ ����. (IMG �������� ��ȯ)
			m_Draw_X += METER_ACROSS_ONE; //�̹��� �ϳ� �ǳʼ� ���
		}

		SetRect(); //Rect ����
	}
}

void FirRing_S::Draw(HDC hdc)
{
	if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRRING_W, FIRRING_S_H);
		BitMapMgr->GetImage(m_IMG_Cash)->DrawTransparent(hdc, m_Draw_X + FIRRING_CASH_X_GAP, m_Draw_Y + FIRRING_CASH_Y_GAP, FIRRING_CASH_W, FIRRING_CASH_H);
	}
}

void FirRing_S::Draw_OnCharacter(HDC hdc)
{
	if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion_R)->DrawTransparent(hdc, m_Draw_X + FIRRING_W, m_Draw_Y, FIRRING_W, FIRRING_S_H);
	}
}

void FirRing_S::DrawCashScoreText(HDC hdc)
{
	std::wstring str;

	SetBkMode(hdc, TRANSPARENT); //���� �޹�� ����ȭ
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255)); //���� �� ����(���)

	SelectObject(hdc, GMMgr->Get_Font(FONT_CASH_SCORE));
	str = L"500";
	//TextOut(hdc, FIRRING_X + 50, FIRRING_Y, str.c_str(), str.length());
	TextOut(hdc, m_Text_X, m_Text_Y, str.c_str(), str.length());
}

void FirRing_S::SetRect()
{ //Rect ����

	//�ε���
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + FIRRING_W;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRRING_COLLIDER_SAMLL_GAP;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + FIRRING_S_H;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRRING_COLLIDER_SAMLL_GAP;

	//����
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top�� bottom�� �����Ǿ��ִ�.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //ĳ���� �ִ� ���� ���̱���
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}