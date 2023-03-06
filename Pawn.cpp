#include "Pawn.h"
#include "GameManager.h"

#define GMMgr GameManager::Get_Instance()

Pawn::Pawn() 
{
	
}

Pawn::Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
	firstMoveCheck = true;
}

Pawn::~Pawn()
{
}

//bool Pawn::ColliderCheck_Piece(POINT point)
//{
//	if (PtInRect(&m_BitMapRect, point))
//	{
//		//TODO::해당 기물의 이동 방향 체크 후. 가로막는 것 없으면 이동.
//		m_moveCheck = true; //이동 표시 체크 요청이 들어왔는지
//		return true;
//	}
//	return false;
//}
//
//bool Pawn::ColliderCheck_CanMove(POINT point)
//{
//	m_moveCheck = false; //
//
//	for (auto rect : m_BitMapRect_MoveList)
//	{
//		if (PtInRect(&rect, point))
//		{
//			//이동할 수 있는 칸을 누른 경우
//			Move(rect);
//			firstMoveCheck = false; //첫번째 이동이후 false로 유지되어야 한다.
//			return true;
//		}
//	}
//
//	//실제 이동이 일어나지 않고 이동 가능 칸 체크만 했을때도 list가 초기화 되어야 한다.
//	//(초기화 하지 않으면 i가 늘어나서 표시가 점진적으로 길게 늘어난다.)
//	m_BitMapRect_MoveList.clear();
//	return false;
//}

void Pawn::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP (*map)[BOARD_Y] = GMMgr->Get_Map();
	CAMP eatableCheck;
	int move_iX = 1;

	//전방 이동
	for (int i = 1; i <= PAWN::MAX_MOVE_COUNT; i++)
	{
		//앞으로 한칸(두칸)
		if (map[m_iX][m_iY + move_iY * i] == CAMP_NONE) //진행할 길이 막히지 않으면
		{ //이동 가능한 범위 탐지 > m_BitMapRect_MoveList에 rect push
			RECT TmpRect;
			TmpRect.left = m_iX * IMG_BG_SIZE;
			TmpRect.top = (m_iY + move_iY * i) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
		else
			break;

		//첫번째 이동(두개 이동 가능 턴)을 이미 한 경우
		if (firstMoveCheck == false)
			break;
	}


	//전방 대각선에 적 기물 있으면! 먹기위한 rect세팅(동북, 서북)
	for (int i = 0; i < PAWN::MAX_MOVE_COUNT; i++)
	{
		RECT TmpRect;
		
		switch (i)
		{
		case PAWN::EAT_LEFT:
			eatableCheck = map[m_iX - move_iX][m_iY + move_iY];
			TmpRect.left = (m_iX - move_iX) * IMG_BG_SIZE;
			break;
		case PAWN::EAT_RIGHT:
			eatableCheck = map[m_iX + move_iX][m_iY + move_iY];
			TmpRect.left = (m_iX + move_iX) * IMG_BG_SIZE;
			break;
		}

		if ((eatableCheck != CAMP_NONE) &&
			(eatableCheck != m_CampColor))
		{
			TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
	}
}