#include "FirJar.h"
#include "GameManager.h"

FirJar::FirJar()
{
	m_IMG_NowMotion = IMG_OBJECT_POT_1;
}

FirJar::~FirJar()
{
}

void FirJar::InitialSet(IMG _IMG_X, int _X, int _Y)
{
	m_IMG_NowMotion = _IMG_X;

	m_Draw_X = _X;
	m_Draw_Y = _Y;

	//m_Rect[RECT_BITMAP].right = m_Rect[RECT_BITMAP].left + FIRJAR_W;
	//m_Rect[RECT_BITMAP].bottom = m_Rect[RECT_BITMAP].top + FIRJAR_H;

	//TODO::콜라이더 체크 세팅
	//m_Rect[RECT_COLLIDER]
}

void FirJar::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRJAR_W, FIRJAR_H);
}

void FirJar::Update(float total_MoveDistance, float _Prev_MoveDistance)
{
	//이글거리는 효과
	if (m_IMG_NowMotion == IMG_OBJECT_POT_1)
		m_IMG_NowMotion = IMG_OBJECT_POT_2;
	else
		m_IMG_NowMotion = IMG_OBJECT_POT_1;

	//배경 이동
	m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) * 10;

	if (m_Draw_X <= START_SHOW_X) //가장 처음 이미지가 -x라서 절댓값을 체크한다.
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		m_Draw_X += METER_ACROSS_ONE; //이미지 하나 건너서 출력
	}
	else if (m_Draw_X >= END_SHOW_X)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)
		m_Draw_X -= METER_ACROSS_ONE;
	}
}
