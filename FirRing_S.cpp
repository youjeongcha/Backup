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
		//애니메이션
		Animation(deltaTime);

		//-----------------------

		//불링 이동
		//★ 시간에 따라 움직여야 하는 게 있다면 deltaTime을 곱해준다.★ 
		//시간당 좌표를 이동하는 건 //m_Draw_X -= 5; 하면 된다.
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) + -MOVE_SPEED_FRIE * deltaTime;

		if (m_Draw_X <= START_SHOW_X) //가장 처음 이미지가 -x라서 절댓값을 체크한다.
		{ //앞으로 간다. (IMG 왼쪽으로 순환)
			m_Draw_X += METER_ACROSS_ONE; //이미지 하나 건너서 출력
		}

		SetRect(); //Rect 세팅
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

	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경(흰색)

	SelectObject(hdc, GMMgr->Get_Font(FONT_CASH_SCORE));
	str = L"500";
	//TextOut(hdc, FIRRING_X + 50, FIRRING_Y, str.c_str(), str.length());
	TextOut(hdc, m_Text_X, m_Text_Y, str.c_str(), str.length());
}

void FirRing_S::SetRect()
{ //Rect 세팅

	//부딪힘
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + FIRRING_W;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRRING_COLLIDER_SAMLL_GAP;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + FIRRING_S_H;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRRING_COLLIDER_SAMLL_GAP;

	//점수
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //캐릭터 최대 점프 높이까지
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}