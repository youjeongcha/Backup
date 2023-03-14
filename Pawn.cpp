#include "Pawn.h"
#include "GameManager.h"


Pawn::Pawn(Piece _piece, IMG _Index) : Piece(_piece)
{
	//승진을 위해서 이 멤버 이니셜라이저는 사용하지 않는다.
	/*m_Piece = _Index;
	m_pBitMap = GMMgr->Get_BitMapMain()->GetImage(_Index);*/
}

Pawn::Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
	firstMoveCheck = true;
}

Pawn::~Pawn()
{
}


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
	//+앙파상 기능
	for (int i = 0; i < PAWN::MAX_MOVE_COUNT; i++)
	{
		RECT TmpRect;
		
		//먹을 기물이 특정 좌표에 있는지 확인을 하기 위한 세팅
		//left값이 특이점이기에 별도 세팅을 해준다.
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

		//해당 기물을 먹고 차지하게될 자리를(rect) 세팅한다.

		//대각선 앞에 상대방의 기물이 있는 경우 + 앙파상(적 기물을 먹는 시점)
		if ((eatableCheck != CAMP_NONE) &&
			(eatableCheck != m_CampColor))
		{
			TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
	}

	////☆+앙파상 기능//삭제를 위해선 갈아 엎어야 해서 삭제 전까지(이동)만 구현
	//for (int i = ENPASSANT_LEFT; i <= PAWN::ENPASSANT_RIGHT; i++)
	//{
	//	RECT TmpRect;

	//	//먹을 기물이 특정 좌표에 있는지 확인을 하기 위한 세팅
	//	//left값이 특이점이기에 별도 세팅을 해준다.
	//	switch (i)
	//	{
	//	case PAWN::ENPASSANT_LEFT:
	//		eatableCheck = map[m_iX - move_iX][m_iY];
	//		TmpRect.left = (m_iX - move_iX) * IMG_BG_SIZE;
	//		break;
	//	case PAWN::ENPASSANT_RIGHT:
	//		eatableCheck = map[m_iX + move_iX][m_iY];
	//		TmpRect.left = (m_iX + move_iX) * IMG_BG_SIZE;
	//		break;
	//	}

	//	//해당 기물을 먹고 차지하게될 자리를(rect) 세팅한다.

	//	//left나 right에 직전 턴에 2칸 이동한 상대방의 기물이 있는 경우 + 앙파상(적 기물을 먹는 시점)
	//	if ((eatableCheck != CAMP_NONE) &&
	//		(eatableCheck != m_CampColor))
	//	{
	//		TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
	//		TmpRect.right = TmpRect.left + IMG_BG_SIZE;
	//		TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
	//		m_BitMapRect_MoveList.push_back(TmpRect);
	//	}
	//}
}