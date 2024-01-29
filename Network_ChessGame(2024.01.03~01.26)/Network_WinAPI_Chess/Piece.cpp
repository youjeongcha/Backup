#include "Piece.h"
#include "GameManager.h"
//#include "PiecesManager.h"
//
//#define GMMgr GameManager::Get_Instance()
//#define PiecesMgr PiecesManager::Get_Instance()
//★GameManager.h에다 선언해두고 사용한다. cpp마다 중복 선언할 필요 없이


Piece::Piece(Piece* piece)
//Piece::Piece(Piece* piece)
{
	m_moveCheck = false;

	//m_pBitMap = piece.m_pBitMap;
	//m_pBitMap_Move = piece.m_pBitMap_Move; //이동 표시
	//m_moveCheck = piece.m_moveCheck; //이동 표시 체크 요청이 들어왔는지
	//m_BitMapRect = piece.m_BitMapRect;
	////m_moveRect; //이동 시킬 rect 임시 저장용
	//m_BitMapRect_MoveList = piece.m_BitMapRect_MoveList;
	//m_iX = piece.m_iX; //map에서의 인덱스
	//m_iY = piece.m_iY;
	//move_iY = piece.move_iY; //BW 별 이동 방향 저장
	//m_Piece = piece.m_Piece; //해당 기물의 enum;
	//m_CampColor = piece.m_CampColor; //해당 기물의 진영

	//m_pBitMap = piece.m_pBitMap;
	m_pBitMap_Move = piece->m_pBitMap_Move; //이동 표시
	m_moveCheck = piece->m_moveCheck; //이동 표시 체크 요청이 들어왔는지
	m_BitMapRect = piece->m_BitMapRect;
	//m_moveRect; //이동 시킬 rect 임시 저장용
	m_BitMapRect_MoveList = piece->m_BitMapRect_MoveList;
	m_iX = piece->m_iX; //map에서의 인덱스
	m_iY = piece->m_iY;
	move_iY = piece->move_iY; //BW 별 이동 방향 저장
	m_Piece = piece->m_Piece; //해당 기물의 enum;
	m_CampColor = piece->m_CampColor; //해당 기물의 진영
}

Piece::Piece(BitMapManager& BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y)
{
	m_moveCheck = false;

    m_CampColor = _campColor;
    m_Piece = _Index;
    m_pBitMap = BitMapMgr_Main.GetImage(_Index);
    m_pBitMap_Move = BitMapMgr_Main.GetImage(IMG_MOVE);
    
    this->m_iX = _X;
    this->m_iY = _Y;

	switch (m_CampColor)
	{
	case CAMP_WHITE:
		move_iY = -1;
		break;
	case CAMP_BLACK:
		move_iY = 1;
		break;
	default:
		break;
	}

    m_BitMapRect.left = _X * IMG_BG_SIZE;
    m_BitMapRect.top = _Y * IMG_BG_SIZE;
    m_BitMapRect.right = m_BitMapRect.left + IMG_BG_SIZE;
    m_BitMapRect.bottom = m_BitMapRect.top + IMG_BG_SIZE;
}

Piece::~Piece()
{
}


bool Piece::ColliderCheck_Piece(POINT point)
{
	//검은, 흰 말을 클릭했는지 and 해당 말이 움직일 턴이 맞는지(해당 순서에만 말 선택 가능)
	//★턴 확인은 get으로 PieceMgr에서 반복문 들어오기 전에 확인
	if (PtInRect(&m_BitMapRect, point))//) &&(GMMgr->Get_PlayerTurn() == m_CampColor))
	{
		//해당 기물의 이동 방향 체크 후. 가로막는 것 없으면 이동.
		m_moveCheck = true; //이동 표시 체크 요청이 들어왔는지
		return true;
	}
	return false;
}

bool Piece::ColliderCheck_Moveable(POINT point)
{
	m_moveCheck = false;

	for (auto rect : m_BitMapRect_MoveList)
	{
		if (PtInRect(&rect, point))
		{
			//좌표 이동 : 이동할 수 있는 칸을 누른 경우
			m_moveRect = rect;
			firstMoveCheck = false; //첫번째 이동이후 false로 유지되어야 한다.

			////이전의 move 상태를 파악
			//if (m_MoveState == CAN_FIRSTMOVE)
			//{
			//	//(캐슬링 미구현)King은 캐슬링을 위해 CAN_FIRSTMOVE > CASTLING > NONE의 상태로 전환
			//	//Pawn이 처음 이동하는 경우 
			//	if (m_Piece == IMG_BLACK_PAWN || m_Piece == IMG_WHITE_PAWN)
			//	{

			//	}
			//}
			return true;
		}
	}

	//실제 이동이 일어나지 않고 이동 가능 칸 체크만 했을때도 list가 초기화 되어야 한다.
	//(초기화 하지 않으면 i가 늘어나서 표시가 점진적으로 길게 늘어난다.)
	m_BitMapRect_MoveList.clear();
	return false;
}

//★peice SetMoveableRect는 가상함수로 사용한다.
//void Piece::SetMoveableRect()
//{
//
//}

void Piece::DrawMoveable(HDC hdc)
{	//m_BitMapRect_MoveList에 미리 넣어둔 이미지 출력하기
	//PRINT_XY_PLUS 중앙에 출력 위해
	for (auto rect : m_BitMapRect_MoveList)
		m_pBitMap_Move->Draw(hdc, rect.left + PRINT_XY_PLUS, rect.top + PRINT_XY_PLUS, IMG_SIZE, IMG_SIZE);
}


void Piece::Move()
{
	//현재 칸 비우기
	GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);

	//m_moveRect이 이동해야 할 위치를 가지고 있고
	//m_iX, m_iY들을 map에서 사용할 인덱스
    m_iX = m_moveRect.left / IMG_BG_SIZE;
    m_iY = m_moveRect.top / IMG_BG_SIZE;

	m_BitMapRect = m_moveRect;

	//이동할 칸 기물 진영이 차지한다 전달
    //XY좌표 ID 값으로 GM의 CAMP형 Map에 현재 map상황을 전달해준다.
    GMMgr->Set_Map(m_CampColor, m_iX, m_iY);
    m_BitMapRect_MoveList.clear();
}

void Piece::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_iX * IMG_BG_SIZE + PRINT_XY_PLUS, m_iY * IMG_BG_SIZE + PRINT_XY_PLUS, IMG_SIZE, IMG_SIZE);
}


void Piece::Set_Rect(CAMP map[][BOARD_Y], int move_iX, int move_iY, int count)
{
	CAMP moveableCheck;
	bool eatableCheck;

	for (int i = 1; i <= count; i++)
	{
		moveableCheck = map[m_iX + move_iX * i][m_iY + move_iY * i];
		eatableCheck = (moveableCheck != CAMP_NONE) && (moveableCheck != m_CampColor);

		if ((moveableCheck == CAMP_NONE) || (eatableCheck))
		{
			RECT TmpRect;
			TmpRect.left = (m_iX + move_iX * i) * IMG_BG_SIZE;
			TmpRect.top = (m_iY + move_iY * i) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);

			if (eatableCheck)
				break;
		}
		else
			break;
	}
}


//체스 네트워크 추가 코드


void Piece::MovePieceData()
{
	//말 움직이기 전 map의 인덱스를 저장해둬야. 다른 플레이어가 이동할 말을 판별할 수 있다.
	GMMgr->Set_moveData(m_iX, m_iY, m_moveRect);
}