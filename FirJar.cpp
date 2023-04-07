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

	//Rect 세팅
	SetRect();
}

void FirJar::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRJAR_W, FIRJAR_H);
}

void FirJar::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{
	//애니메이션
	Animation(deltaTime);

	//-----------------------

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

	SetRect(); //Rect 세팅
}

void FirJar::Animation(float deltaTime)
{ //이글거리는 애니메이션

	if (m_Time >= ANI_FIREJAR)
	{
		m_Time = 0;
		
		if (m_IMG_NowMotion == IMG_OBJECT_POT_1)
			m_IMG_NowMotion = IMG_OBJECT_POT_2;
		else
			m_IMG_NowMotion = IMG_OBJECT_POT_1;
	}

	m_Time += deltaTime;
}

void FirJar::SetRect()
{
	//Rect 세팅
	m_Collider_Rect.left = m_Draw_X - FIREJAR_RECT_GAP;
	m_Collider_Rect.top = m_Draw_Y - FIREJAR_RECT_GAP;
	m_Collider_Rect.right = m_Collider_Rect.left + FIRJAR_W;
	m_Collider_Rect.bottom = m_Collider_Rect.top + FIRJAR_H;
}
