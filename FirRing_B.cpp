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

	//Rect 세팅
	SetRect();
}

void FirRing_B::Draw(HDC hdc)
{
	//불링 화면상에 나타날 시점에 사용
	//if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_Draw_X, m_Draw_Y, FIRRING_W, FIRRING_H);
	}
}

void FirRing_B::Draw_OnCharacter(HDC hdc)
{
	//불링 화면상에 나타날 시점에 사용
	//if (m_UsingCheck == true)
	{
		BitMapMgr->GetImage(m_IMG_NowMotion_R)->DrawTransparent(hdc, m_Draw_X + FIRRING_W, m_Draw_Y, FIRRING_W, FIRRING_H);
	}
}

void FirRing_B::Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance)
{
	//불링 화면상에 나타날 시점에 사용
	//if (m_UsingCheck == true)
	{
		//애니메이션
		Animation(deltaTime);

		//-----------------------

		//불링 이동
		//★ 시간에 따라 움직여야 하는 게 있다면 deltaTime을 곱해준다.★ 
		//시간당 좌표를 이동하는 건 //m_Draw_X -= 5; 하면 된다.
		m_Draw_X += (_Prev_MoveDistance - total_MoveDistance) + -MOVE_SPEED_FRIERING_B * deltaTime;

		//Goal이 특정 좌표에 오면 순환을 멈춘다.
		//if (GMMgr->Get_GoalEndPositionCheck() == false)
		{
			//m_UsingCheck = true; //링 생성 멈췄다가 다시 생성하는 경우를 위해

			if (m_Draw_X <= START_SHOW_X) //가장 처음 이미지가 -x라서 절댓값을 체크한다.
			{ //앞으로 간다. (IMG 왼쪽으로 순환)
				m_bActiveCheck = true;
				m_Draw_X += METER_ACROSS_ONE; //이미지 하나 건너서 출력
			}
			else if (m_Draw_X >= END_SHOW_X)
			{ //뒤로 간다. (IMG 오른쪽으로 순환)
				m_Draw_X -= METER_ACROSS_ONE;
			}
		}
		//else //Goal이 특정 좌표에 오면 순환을 멈춘다.
		//{
		//	if (m_Draw_X <= START_SHOW_X) //가장 처음 이미지가 -x라서 절댓값을 체크한다.
		//	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		//		m_UsingCheck = false;
		//	}
		//}

		SetRect(); //Rect 세팅
	}
}

void FirRing_B::Animation(float deltaTime)
{ //이글거리는 애니메이션
	//불링 화면상에 나타날 시점에 사용
	//if (m_UsingCheck == true)
	{
		if (m_AnimationTime >= ANI_SPEED_FIRE)
		{
			m_AnimationTime = 0;

			//왼쪽 링
			if (m_IMG_NowMotion == IMG_OBJECT_RING_LEFT_1)
				m_IMG_NowMotion = IMG_OBJECT_RING_LEFT_2;
			else
				m_IMG_NowMotion = IMG_OBJECT_RING_LEFT_1;

			//오른쪽 링
			if (m_IMG_NowMotion_R == IMG_OBJECT_RING_RIGHT_1)
				m_IMG_NowMotion_R = IMG_OBJECT_RING_RIGHT_2;
			else
				m_IMG_NowMotion_R = IMG_OBJECT_RING_RIGHT_1;
		}

		m_AnimationTime += deltaTime;
	}
}

void FirRing_B::SetRect()
{ //Rect 세팅


	//부딪힘
	m_Collider_Rect[RECT_BUMP].left = m_Draw_X + FIRRING_W;
	m_Collider_Rect[RECT_BUMP].right = m_Collider_Rect[RECT_BUMP].left + FIRRING_COLLIDER_W;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_BUMP].top = m_Draw_Y + FIRRING_H;
	m_Collider_Rect[RECT_BUMP].bottom = m_Collider_Rect[RECT_BUMP].top + FIRRING_COLLIDER_H;

	//점수
	m_Collider_Rect[RECT_SCORE].left = m_Collider_Rect[RECT_BUMP].left;
	m_Collider_Rect[RECT_SCORE].right = m_Collider_Rect[RECT_BUMP].right;
	//top과 bottom은 고정되어있다.
	m_Collider_Rect[RECT_SCORE].top = CHARACTER_JUMP_MAX_Y; //캐릭터 최대 점프 높이까지
	m_Collider_Rect[RECT_SCORE].bottom = m_Collider_Rect[RECT_BUMP].top - 1;
}