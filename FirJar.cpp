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
	m_Draw_X += (_Prev_MoveDistance - total_MoveDistance);// *10;

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
{//Rect 세팅
	
	//부딪힘
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + BUMP_RECT_GAP;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRJAR_COLLIDER_W;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + BUMP_RECT_GAP;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRJAR_COLLIDER_H;

	//점수
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //캐릭터 최대 점프 높이까지
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}
