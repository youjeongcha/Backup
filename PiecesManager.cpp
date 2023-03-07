#include "PiecesManager.h"
#include "GameManager.h"

#define GMMgr GameManager::Get_Instance()

PiecesManager* PiecesManager::m_pInstance = NULL;



PiecesManager::PiecesManager()
{
	m_MoveTurn = false;
}

PiecesManager::~PiecesManager()
{
	for (int i = 0; i < CAMP_COUNT; i++)
	{
		for (int j = 0; j < CAMP_PIECE_COUNT; j++)
			delete m_Pieces[i][j];
	}
}

void PiecesManager::Init(BitMapManager* BitMapMgr_Main)
{
	InitLoaction(BitMapMgr_Main);
	
	/*int black_PieceCount = 0;
	int white_PieceCount = 0;

	MakePieces<Pawn>(BitMapMgr_Main, IMG_BLACK_PAWN, FIRST_PAWN_X, BLACK_PAWN_Y, PIECES_PAWN);
	//폰
	/*for (auto _piece : )
	{
		switch (_piece->Get_CampColor())
		{
		case CAMP_BLACK:
			m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
			break;
		case CAMP_WHITE:
			m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
			break;
		}
	}*/

	//룩
	//for (auto _piece : MakePieces<Pawn>(BitMapMgr_Main, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y, PIECES_ROOK))
	//{
	//	switch (_piece->Get_CampColor())
	//	{
	//	case CAMP_BLACK:
	//		m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
	//		break;
	//	case CAMP_WHITE:
	//		m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
	//		break;
	//	}
	//}

	////나이트
	//for (auto _piece : MakePieces<Knight>(BitMapMgr_Main, IMG_BLACK_KNIGHT, FIRST_KNIGHT_X, BLACK_OTHER_Y, PIECES_KNIGHT))
	//{
	//	switch (_piece->Get_CampColor())
	//	{
	//	case CAMP_BLACK:
	//		m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
	//		break;
	//	case CAMP_WHITE:
	//		m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
	//		break;
	//	}
	//}

	////비숍
	//for (auto _piece : MakePieces<Bishop>(BitMapMgr_Main, IMG_BLACK_BISHOP, FIRST_BISHOP_X, BLACK_OTHER_Y, PIECES_BISHOP))
	//{
	//	switch (_piece->Get_CampColor())
	//	{
	//	case CAMP_BLACK:
	//		m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
	//		break;
	//	case CAMP_WHITE:
	//		m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
	//		break;
	//	}
	//}

	////퀸
	//for (auto _piece : MakePieces<Queen>(BitMapMgr_Main, IMG_BLACK_QUEEN, QUEEN_X, BLACK_OTHER_Y, PIECES_QUEEN))
	//{
	//	switch (_piece->Get_CampColor())
	//	{
	//	case CAMP_BLACK:
	//		m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
	//		break;
	//	case CAMP_WHITE:
	//		m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
	//		break;
	//	}
	//}


	////킹
	//for (auto _piece : MakePieces<Pawn>(BitMapMgr_Main, IMG_BLACK_KING, KING_X, BLACK_OTHER_Y, PIECES_KING))
	//{
	//	switch (_piece->Get_CampColor())
	//	{
	//	case CAMP_BLACK:
	//		m_Pieces[CAMP_BLACK][black_PieceCount++] = _piece;
	//		break;
	//	case CAMP_WHITE:
	//		m_Pieces[CAMP_WHITE][white_PieceCount++] = _piece;
	//		break;
	//	}
	//}*/

	//m_Pieces[CAMP_BLACK][black_PieceCount++] = new Knight(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KNIGHT, FIRST_KNIGHT_X, BLACK_OTHER_Y);
	//m_Pieces[CAMP_BLACK][black_PieceCount++] = new Bishop(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_BISHOP, FIRST_BISHOP_X, BLACK_OTHER_Y);
	//m_Pieces[CAMP_BLACK][black_PieceCount++] = new Queen(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_QUEEN, QUEEN_X, BLACK_OTHER_Y);
	//m_Pieces[CAMP_BLACK][black_PieceCount++] = new King(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KING, KING_X, BLACK_OTHER_Y);
	
}



void PiecesManager::InitLoaction(BitMapManager* BitMapMgr_Main)
{
	//int black_Y = 1; //흑말 기준의 폰 시작 y index
	//int next_Y; //흰말 검은말 대칭이라 y축 변경이 달라야 한다.
	//int oneLinePieces = CAMP_PIECE_COUNT / 2; //한줄에 올 수 있는 말의 개수 8
	//int halfLinePieces = oneLinePieces / 2; //한줄의 절반 말 개수 4
	//int x_Symmetry = 7; //좌우 대칭 확인 위해 x축 대칭의 합
	//int y_Pawn_Gap = 5; //흑백 말 Pawn의 y좌표 차이값
	//int y_Pawn_Gap = 7; //흑백 말 Pawn 제외 y좌표 차이값
	int pieceCount = 0;
	IMG pieceIndex;
	//Piece* tmpPiece;

	//switch (campColor)
	//{
	//case CAMP_WHITE:
	//	y = 1;
	//	next_Y = -1;
	//	break;
	//case CAMP_BLACK:
	//	y = 6;
	//	next_Y = 1;
	//	break;
	//default:
	//	break;
	//}

	//폰이 있는 줄 > 다른 말의 줄 순서 초기화

	//폰
	for (int x = 0; x <= ONELINE_PIECES_COUNT; x++) //말의 개수이자 x축의 id number
	{
		//tmpPiece = new Pawn(*BitMapMgr_Main, campColor, pieceIndex, x, y);
		m_Pieces[CAMP_BLACK][pieceCount] = new Pawn(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_PAWN, x, BLACK_PAWN_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Pawn(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_PAWN, x, WHITE_PAWN_Y);
		//m_Pieces[campColor][pieceCount++]->Init(BitMapMgr_Main, campColor, pieceIndex, x, y);
	}

	//y += next_Y;

	//pieceIndex = (IMG)(pieceIndex + 1);
	
	//MakePiece<Rook>(BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);


	//룩*2
	//for (int x = 0; x < PIECES_ROOK; x++) //말의 개수이자 x축의 id number
	{
		m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Rook(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_ROOK, FIRST_ROOK_X, WHITE_OTHER_Y);

		m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, SECOND_ROOK_X, BLACK_OTHER_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Rook(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_ROOK, SECOND_ROOK_X, WHITE_OTHER_Y);
	}

	//나이트*2
	m_Pieces[CAMP_BLACK][pieceCount] = new Knight(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KNIGHT, FIRST_KNIGHT_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Knight(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KNIGHT, FIRST_KNIGHT_X, WHITE_OTHER_Y);


	m_Pieces[CAMP_BLACK][pieceCount] = new Knight(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KNIGHT, SECOND_KNIGHT_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Knight(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KNIGHT, SECOND_KNIGHT_X, WHITE_OTHER_Y);

	//비숍*2
	m_Pieces[CAMP_BLACK][pieceCount] = new Bishop(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_BISHOP, FIRST_BISHOP_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Bishop(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_BISHOP, FIRST_BISHOP_X, WHITE_OTHER_Y);

	m_Pieces[CAMP_BLACK][pieceCount] = new Bishop(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_BISHOP, SECOND_BISHOP_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Bishop(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_BISHOP, SECOND_BISHOP_X, WHITE_OTHER_Y);

	//퀸
	m_Pieces[CAMP_BLACK][pieceCount] = new Queen(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_QUEEN, QUEEN_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Queen(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_QUEEN, QUEEN_X, WHITE_OTHER_Y);

	//킹
	m_Pieces[CAMP_BLACK][pieceCount] = new King(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KING, KING_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new King(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KING, KING_X, WHITE_OTHER_Y);

	//for (int x = 0; x < HALFLINE_PIECES_COUNT; x++)
	//{
	//	//대칭되는 같은 말 세팅(룩, 나이트, 비숍)
	//	//m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);
	//	//Piece tmpPiece1 = Piece(*BitMapMgr_Main, campColor, pieceIndex, x, y);
	//	//m_Pieces[campColor][pieceCount++] = &tmpPiece1;
	//	//m_Pieces[campColor][pieceCount++]->Init(BitMapMgr_Main, campColor, pieceIndex, x, y);

	//	if (x == PIECES::PIECES_QUEEN - 1) //퀸과 킹은 다르게 세팅 필요
	//		pieceIndex = (IMG)(pieceIndex + 1);

	//	//Piece tmpPiece2 = Piece(*BitMapMgr_Main, campColor, pieceIndex, x_Symmetry - x, y);
	//	//m_Pieces[campColor][pieceCount++] = &tmpPiece2;
	//	//m_Pieces[campColor][pieceCount++]->Init(BitMapMgr_Main, campColor, pieceIndex, x_Symmetry - x, y);

	//	pieceIndex = (IMG)(pieceIndex + 1);
	//}
}

bool PiecesManager::ColliderCheck(POINT point)
{
	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			if (m_MoveTurn == false)
			{//이동 가능 이미지 콜라이더 rect 적용(말 클릭 안 했을 시 이동 가능해버리면 안되므로)
				if (m_Pieces[campColor][piece]->ColliderCheck_Piece(point))
				{//기물 이동 클릭
					m_MoveTurn = true;
					return true;
				}
			}
			else
			{
				if (m_Pieces[campColor][piece]->ColliderCheck_Moveable(point))
				{//이동 movealbe 클릭
					m_MoveTurn = false;

					//적 기물을 먹는 경우
					PieceErase(campColor, piece);

					//XY 좌표와 Rect 이동
					m_Pieces[campColor][piece]->Move();

					if (GMMgr->Get_GameEndCheck() == false)
						//현재 턴과 반대되는 턴을 세팅해준다.(플레이어 턴 전환)
					GMMgr->Set_PlayerTurn();

					return true;
				}
			}
		}
	}

	//초기화 필요
	//이동하지 않고 이동 가능 rect 밖을 클릭한 경우 : 해당 말 이동 취소
	if (m_MoveTurn)
	{
		m_MoveTurn = false;
		return true;
	}

	return false;
}

void PiecesManager::PieceErase(int _campColor, int _piece)
{//TODO::적 기물을 먹는 경우

	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();
	IMG IMG_PieceType;

	//특정 위치로 이동할 기물
	RECT moveRect = m_Pieces[_campColor][_piece]->Get_moveRect();
	CAMP moveCampColor = m_Pieces[_campColor][_piece]->Get_CampColor();

	//moveRect의 Piece가 이동할 위치에 있는 기물
	RECT bitmapRect;
	CAMP bitmapCampColor = map[moveRect.left / IMG_BG_SIZE][moveRect.top / IMG_BG_SIZE];


	if (bitmapCampColor != CAMP_NONE &&
		bitmapCampColor != moveCampColor)
	{
		//m_Pieces 돌리면서 겹치는 것이 있는지 확인
		for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
		{
			for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
			{
				bitmapCampColor = m_Pieces[campColor][piece]->Get_CampColor();
				bitmapRect = m_Pieces[campColor][piece]->Get_BitMapRect();

				if ((bitmapRect.left == moveRect.left) &&
					(bitmapRect.top == moveRect.top))
				{
					//GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);
					m_Pieces[campColor][piece]->Set_Inactive();

					//게임 승리 체크
					//킹인지 체크 위해
					IMG_PieceType = m_Pieces[campColor][piece]->Get_PieceType();

					if ((IMG_PieceType == IMG_BLACK_KING) || (IMG_PieceType == IMG_WHITE_KING))
						GMMgr->Set_GameEndCheck(true);

					return;
				}
			}
		}
	}
}

void PiecesManager::DrawPices(HDC hdc)
{
	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			m_Pieces[campColor][piece]->Draw(hdc);
			//m_Pieces[campColor][piece]->CanMoveDraw(hdc);
		}
	}
}

void PiecesManager::DrawMoveable(HDC hdc)
{
	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			//이동 표시 체크 요청이 들어왔는지
			if (m_Pieces[campColor][piece]->Get_MoveCheck())
			{
				m_Pieces[campColor][piece]->SetMoveableRect();
				m_Pieces[campColor][piece]->DrawMoveable(hdc);
				return;
			}
		}
	}
}
