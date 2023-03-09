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

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		m_promotionRect[i].left = PROMOTION_RECT_L;
		m_promotionRect[i].top = PROMOTION_RECT_T + PROMOTION_RECT_GAP * i;
		m_promotionRect[i].right = PROMOTION_RECT_R;
		m_promotionRect[i].bottom = PROMOTION_RECT_B + PROMOTION_RECT_GAP * i;
	}
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
	Piece* pieceTmp;

	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			pieceTmp = m_Pieces[campColor][piece];

			//기물 클릭
			if (m_MoveTurn == false)
			{//이동 가능 이미지 콜라이더 rect 적용(말 클릭 안 했을 시 이동 가능해버리면 안되므로)
				if (pieceTmp->ColliderCheck_Piece(point))
				{//기물 이동 클릭
					m_MoveTurn = true;
					return true;
				}
			}
			else
			{//기물의 moveable 클릭
				if (pieceTmp->ColliderCheck_Moveable(point))
				{//이동 movealbe 클릭
					m_MoveTurn = false;

					//적 기물을 먹는 경우
					PieceErase(campColor, piece); //현재 움직이는 말의 정보

					//XY 좌표와 Rect 이동
					pieceTmp->Move();


					//Pawn이 상대측 y축 끝까지 도달 > 승진 진행
					if (PawnPromotionCheck(pieceTmp))
					{
						//승진중에 입력 막기
						GMMgr->Set_GameStopCheck(true);
						m_ErasePawn = pieceTmp;
						GMMgr->Set_PlayerTurn();
						InvalidateRect(GMMgr->Get_HWND_Sub_Promotion(), NULL, true);
					}

					if (GMMgr->Get_GameStopCheck() == false)
					{
						//현재 턴과 반대되는 턴을 세팅해준다.(플레이어 턴 전환)
						GMMgr->Set_PlayerTurn();
					}


					//sub Window 색상 변경 위해
					InvalidateRect(GMMgr->Get_HWND_Sub(), NULL, true);

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

bool PiecesManager::PawnPromotionCheck(Piece* pieceTmp)
{
	//Pawn이 상대측 y축 끝까지 도달 > 승진
	switch (pieceTmp->Get_PieceType())
	{
	case IMG_BLACK_PAWN:
		if (pieceTmp->Get_iY() == WHITE_END_Y)
			return true;
		break;
	case IMG_WHITE_PAWN:
		if (pieceTmp->Get_iY() == BLACK_END_Y)
			return true;
		break;
	}

	return false;
}

bool PiecesManager::ColliderCheck_SubPromotion(POINT point)
{
	Piece* newPiece;
	CAMP campColor = m_ErasePawn->Get_CampColor();
	//이미지 B W 구분 설정을 위해 
	IMG imgColor = (IMG)(campColor == CAMP_BLACK) ? IMG_BLACK_START : IMG_WHITE_START;

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		if (PtInRect(&m_promotionRect[i], point)) //승진 선택지를 고른 경우
		{
			//새 기물을 넣어주어야 하기 때문에 주소를 찾기 위해서
			for (int j = 0; j < CAMP_PIECE_COUNT; j++)
			{
				if (m_ErasePawn == m_Pieces[campColor][j])
				{
					switch (m_promotionRect[i].top)
					{
					case PROMOTION_ROOK_T:
						newPiece = new Rook(*m_ErasePawn, IMG(imgColor + PROMOTION_ROOK));
						break;
					case PROMOTION_KNIGHT_T:
						newPiece = new Knight(*m_ErasePawn, IMG(imgColor + PROMOTION_KNIGHT));
						break;
					case PROMOTION_BISHOP_T:
						newPiece = new Bishop(*m_ErasePawn, IMG(imgColor + PROMOTION_BISHOP));
						break;
					case PROMOTION_QUEEN_T:
						newPiece = new Queen(*m_ErasePawn, IMG(imgColor + PROMOTION_QUEEN));
						break;
					}

					delete m_ErasePawn;
					m_Pieces[campColor][j] = newPiece;

					return true;
				}
			}
		}
	}
	return false;
}

void PiecesManager::DrawPawnPromotion(HDC hdc_SubPromotion)
{
	std::wstring str;
	HFONT font = CreateFont(PROMOTION_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");


	//글자 크기 변경
	SelectObject(hdc_SubPromotion, font);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc_SubPromotion, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc_SubPromotion, RGB(255, 255, 255)); //글자 색 변경

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		switch (m_promotionRect[i].top)
		{
		case PROMOTION_ROOK_T:
			str = L"R o o k";
			break;
		case PROMOTION_KNIGHT_T:
			str = L"K n i g h t";
			break;
		case PROMOTION_BISHOP_T:
			str = L"B i s h o p";
			break;
		case PROMOTION_QUEEN_T:
			str = L"Q u e e n";
			break;
		}

		DrawText(hdc_SubPromotion, str.c_str(), -1, &m_promotionRect[i], DT_CENTER | DT_WORDBREAK);
	}
}

void PiecesManager::PieceErase(int _campColor, int _piece)
{//적 기물을 먹는 경우 //현재 움직이는 말의 정보

	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//특정 위치로 이동할 기물
	Piece* movePiece = m_Pieces[_campColor][_piece];
	RECT moveRect = movePiece->Get_moveRect();
	//CAMP moveCampColor = movePiece->Get_CampColor();

	//moveRect의 Piece가 이동할 위치에 있는 기물
	RECT delete_BitmapRect;
	CAMP delete_bitmapCampColor = map[moveRect.left / IMG_BG_SIZE][moveRect.top / IMG_BG_SIZE];
	//먹히는 기물의 종류 체크 위해
	IMG delete_IMG_PieceType;

	//앙파상용 : moveRect의 Piece가 이동할 위치에 있는 기물
	//IMG movePieceType = movePiece->Get_PieceType();


	if ((delete_bitmapCampColor != CAMP_NONE) &&
		(delete_bitmapCampColor != movePiece->Get_CampColor()))
	{
		//m_Pieces 돌리면서 겹치는 것이 있는지 확인
		for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
		{
			for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
			{
				//moveCampColor = m_Pieces[campColor][piece]->Get_CampColor();
				delete_BitmapRect = m_Pieces[campColor][piece]->Get_BitMapRect();

				//폰과 킹을 체크 위해
				//delete_IMG_PieceType = m_Pieces[campColor][piece]->Get_PieceType();


				////앙파상
				////움직이고 있는 PAWN
				//switch (movePieceType)
				//{
				//case IMG_BLACK_PAWN :
				//	//TODO::목표 상대가 지난턴 2칸 움직인 폰인지 확인(2칸!)
				//	if (delete_IMG_PieceType == IMG_WHITE_PAWN)
				//	{
				//		m_Pieces[campColor][piece].
				//	}
				//	break;
				//case IMG_WHITE_PAWN:
				//	//TODO::목표 상대가 지난턴 2칸 움직인 폰인지 확인(2칸!)
				//	if (delete_IMG_PieceType == IMG_BLACK_PAWN)
				//	{
				//	}
				//	break;
				//default:
				//	break;
				//}


				//일반적인 movableRect와 삭제될 말이 겹치는 경우
				if ((delete_BitmapRect.left == moveRect.left) && (delete_BitmapRect.top == moveRect.top))
				{
					//GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);
					//기물을 시야에서 지우고 비활성화
					m_Pieces[campColor][piece]->Set_Inactive();

					//게임 승리 체크
					//킹인지 체크 위해
					delete_IMG_PieceType = m_Pieces[campColor][piece]->Get_PieceType();

					if ((delete_IMG_PieceType == IMG_BLACK_KING) || (delete_IMG_PieceType == IMG_WHITE_KING))
					{
						GMMgr->Set_GameStopCheck(true);
						GMMgr->Set_GameEndCheck(true);
					}

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
