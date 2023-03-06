#include "Piece.h"
#include "GameManager.h"
#include "PiecesManager.h"

#define GMMgr GameManager::Get_Instance()
#define PiecesMgr PiecesManager::Get_Instance()

Piece::Piece()
{
}

//Piece::Piece(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y)
Piece::Piece(BitMapManager& BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y)
{
    m_CampColor = _campColor;
    m_Piece = _Index;
    m_pBitMap = BitMapMgr_Main.GetImage(_Index);
    m_pBitMap_Move = BitMapMgr_Main.GetImage(IMG_MOVE);
    
    m_iX = _X;
    m_iY = _Y;

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

//void Piece::Init(BitMapManager* BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y)
//{
//    m_CampColor = _campColor;
//	m_Piece = _Index;
//	m_pBitMap = BitMapMgr_Main->GetImage(_Index);
//    m_pBitMap_Move = BitMapMgr_Main->GetImage(IMG_MOVE);
//	//TODO::xy를 받아와서 세팅할건지. 생성자에서 각각 세팅할건지.
//	//Set_XY(_X, _Y);
//}

bool Piece::ColliderCheck_Piece(POINT point)
{
	if (PtInRect(&m_BitMapRect, point))
	{
		//TODO::해당 기물의 이동 방향 체크 후. 가로막는 것 없으면 이동.
		m_moveCheck = true; //이동 표시 체크 요청이 들어왔는지
		return true;
	}
	return false;
}

bool Piece::ColliderCheck_Moveable(POINT point)
{
	m_moveCheck = false; //

	for (auto rect : m_BitMapRect_MoveList)
	{
		if (PtInRect(&rect, point))
		{
			//TODO::적 기물을 먹는 경우
			//PieceErase(campColor, piece);
			//좌표 이동 : 이동할 수 있는 칸을 누른 경우
			m_moveRect = rect;
			//Move(rect);
			firstMoveCheck = false; //첫번째 이동이후 false로 유지되어야 한다.
			return true;
		}
	}

	//실제 이동이 일어나지 않고 이동 가능 칸 체크만 했을때도 list가 초기화 되어야 한다.
	//(초기화 하지 않으면 i가 늘어나서 표시가 점진적으로 길게 늘어난다.)
	m_BitMapRect_MoveList.clear();
	return false;
}


void Piece::SetMoveableRect()
{
}

void Piece::DrawMoveable(HDC hdc)
{	//m_BitMapRect_MoveList에 미리 넣어둔 이미지 출력하기
	//PRINT_XY_PLUS 중앙에 출력 위해
	for (auto rect : m_BitMapRect_MoveList)
	{//TODO::XY조절
		m_pBitMap_Move->Draw(hdc, rect.left + PRINT_XY_PLUS, rect.top + PRINT_XY_PLUS, IMG_SIZE, IMG_SIZE);
	}
}


void Piece::Move()
{
	//현재 칸 비우기
	GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);

    m_iX = m_moveRect.left / IMG_BG_SIZE;
    m_iY = m_moveRect.top / IMG_BG_SIZE;

	m_BitMapRect = m_moveRect;

	//이동할 칸 기물 진영이 차지한다 전달
    //XY좌표 ID 값으로 GM의 CAMP형 Map에 현재 map상황을 전달해준다.
    GMMgr->Set_Map(m_CampColor, m_iX, m_iY);
	//GMMgr->Set_Map(CAMP(*_Map())[BOARD_Y]);
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


//void Piece::Set_Rect(RECT _rect)
//{
//    m_BitMapRect = _rect;
//}
//void Piece::Set_XY(int _X, int _Y)
//{
//	m_iX = _X;
//	m_iY = _Y;
//
//	m_BitMapRect.left = _X * IMG_BG_SIZE;
//	m_BitMapRect.top = _Y * IMG_BG_SIZE;
//	m_BitMapRect.right = m_BitMapRect.left + IMG_BG_SIZE;
//	m_BitMapRect.bottom = m_BitMapRect.top + IMG_BG_SIZE;
//}
