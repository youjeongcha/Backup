#include "PiecesManager.h"
#include "GameManager.h"

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
	InitLocation(BitMapMgr_Main);

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		m_promotionRect[i].left = PROMOTION_RECT_L;
		m_promotionRect[i].top = PROMOTION_RECT_T + PROMOTION_RECT_GAP * i;
		m_promotionRect[i].right = PROMOTION_RECT_R;
		m_promotionRect[i].bottom = PROMOTION_RECT_B + PROMOTION_RECT_GAP * i;
	}
}



void PiecesManager::InitLocation(BitMapManager* BitMapMgr_Main)
{
	int pieceCount;
	int imgColor;
	int colorPiece_Pawn_Y, colorPiece_Other_Y;

	//폰이 있는 줄 > 다른 말의 줄 순서 초기화

	for (int camp = CAMP_BLACK; camp <= CAMP_WHITE; camp++)
	{
		pieceCount = 0;

		switch (camp)
		{
		case CAMP_BLACK:
			imgColor = IMG_BLACK_START;
			colorPiece_Pawn_Y = BLACK_PAWN_Y;
			colorPiece_Other_Y = BLACK_OTHER_Y;
			break;
		case CAMP_WHITE:
			imgColor = IMG_WHITE_START;
			colorPiece_Pawn_Y = WHITE_PAWN_Y;
			colorPiece_Other_Y = WHITE_OTHER_Y;
			break;
		}

		//폰*8 //★생성 개수와 딱 들어맞는 enum을 쓰기 바람
		for (int x = 0; x < PIECES_PAWN; x++) //말의 개수이자 x축의 id number
			m_Pieces[camp][pieceCount++] = new Pawn(*BitMapMgr_Main, (CAMP)camp, (IMG)(PAWN + imgColor), x, colorPiece_Pawn_Y);

		//룩*2
		m_Pieces[camp][pieceCount++] = new Rook(*BitMapMgr_Main, (CAMP)camp, (IMG)(ROOK + imgColor), FIRST_ROOK_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Rook(*BitMapMgr_Main, (CAMP)camp, (IMG)(ROOK + imgColor), SECOND_ROOK_X, colorPiece_Other_Y);

		//나이트*2
		m_Pieces[camp][pieceCount++] = new Knight(*BitMapMgr_Main, (CAMP)camp, (IMG)(KNIGHT + imgColor), FIRST_KNIGHT_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Knight(*BitMapMgr_Main, (CAMP)camp, (IMG)(KNIGHT + imgColor), SECOND_KNIGHT_X, colorPiece_Other_Y);

		//비숍*2
		m_Pieces[camp][pieceCount++] = new Bishop(*BitMapMgr_Main, (CAMP)camp, (IMG)(BISHOP + imgColor), FIRST_BISHOP_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Bishop(*BitMapMgr_Main, (CAMP)camp, (IMG)(BISHOP + imgColor), SECOND_BISHOP_X, colorPiece_Other_Y);

		//퀸
		m_Pieces[camp][pieceCount++] = new Queen(*BitMapMgr_Main, (CAMP)camp, (IMG)(QUEEN + imgColor), QUEEN_X, colorPiece_Other_Y);

		//킹
		m_Pieces[camp][pieceCount++] = new King(*BitMapMgr_Main, (CAMP)camp, (IMG)(KING + imgColor), KING_X, colorPiece_Other_Y);
	}
}

bool PiecesManager::ColliderCheck(POINT point)
{//★반복문을 다 돌아야 하는 구조가 마음에 들지 않지만 지금와서 고치기에는 코드를 다 뜯어고쳐야 한다. 다음엔 주의 바람
	Piece* pieceTmp;

	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			pieceTmp = m_Pieces[campColor][piece];

			//기물 클릭
			if (m_MoveTurn == false)
			{//이동 가능 이미지 콜라이더 rect 적용(말 클릭 안 했을 시 이동 가능해버리면 안되므로)
				if ((GMMgr->Get_PlayerTurn() == pieceTmp->Get_CampColor()) && (pieceTmp->ColliderCheck_Piece(point)))
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
					
					GMMgr->Set_IsSend_Sever(true);

					

			
					//서버 버전에서는 클라이언트(말 이동 플레이어 : 데이터) > 서버(말 이동 데이터) > 클라이언트x2(이동)으로 진행 
					pieceTmp->MovePieceData();


					//PieceErase()에서 게임 종료 확인 했음
					//if (GMMgr->Get_GameEndCheck())
					//	return true;


					//네트워크에서 서버에게 데이터 전달 전에도 있어야 하고. 전달 받고도 있어야 한다.
					//적 기물을 먹는 경우 + 킹 게임오버 체크 //endCheck와 stopCheck를 조정한다.
					MovingObject_Does_ErasePiece(campColor, piece); //현재 움직이는 말의 정보
					
					//Pawn이 상대측 y축 끝까지 도달 > 승진 진행(킹을 잡은 경우 제외
					if (PawnPromotionCheck(pieceTmp))
					{
						//if (IsDataMoveEnd(pieceTmp->Get_CampColor(), pieceTmp->Get_moveRect().top / 60))
						{
							SetErasePawn(pieceTmp);
							GMMgr->Set_IsPromotion(true);
							GMMgr->Set_GameStopCheck(true); //승진중에 입력 막기
						}
					}

					//------------------------

					//XY 좌표와 Rect 이동 //시각적으로 나타내주기 전 현재 이동중인 기물의 좌표를 이동
					//pieceTmp->Move();

					////PieceErase()에서 게임 종료 확인 했음
					//if (GMMgr->Get_GameEndCheck())
					//	return true;

					////Pawn이 상대측 y축 끝까지 도달 > 승진 진행(킹을 잡은 경우 제외
					//if (PawnPromotionCheck(pieceTmp))
					//{
					//	//승진중에 입력 막기
					//	GMMgr->Set_GameStopCheck(true);
					//	m_ErasePawn = pieceTmp;
					//	//GMMgr->Set_PlayerTurn();
					//	//상태 턴 대기
					//	GMMgr->SetDelayTurn();
					//	InvalidateRect(GMMgr->Get_HWND_Sub_Promotion(), NULL, false);
					//}

					////이동 가능한 위치로 옮기려 하는지 체크
					//if (GMMgr->Get_GameStopCheck() == false)
					//{
					//	//상태 턴 대기
					//	GMMgr->SetDelayTurn();


					//	//현재 턴과 반대되는 턴을 세팅해준다.(플레이어 턴 전환)
					//	//GMMgr->Set_PlayerTurn();
					//}


					////sub Window 색상 변경 위해
					//InvalidateRect(GMMgr->Get_HWND_Sub(), NULL, false);

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
		//if (pieceTmp->Get_iY() == WHITE_END_Y)
		if ((pieceTmp->Get_moveRect().top / 60) == WHITE_END_Y)
			return true;
		break;
	case IMG_WHITE_PAWN:
		//if (pieceTmp->Get_iY() == BLACK_END_Y)
		if (pieceTmp->Get_moveRect().top == BLACK_END_Y)
			return true;
		break;
	}

	return false;
}

bool PiecesManager::ColliderCheck_SubPromotion(POINT point)
{
	//Piece* newPiece;
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
						m_PromotionType = PROMOTION_ROOK_T;
						break;
					case PROMOTION_KNIGHT_T:
						m_PromotionType = PROMOTION_KNIGHT_T;
						break;
					case PROMOTION_BISHOP_T:
						m_PromotionType = PROMOTION_BISHOP_T;
						break;
					case PROMOTION_QUEEN_T:
						//m_PromotionType = (PROMOTION_RECT)m_promotionRect[i].top;
						m_PromotionType = PROMOTION_QUEEN_T;

						//newPiece = new Queen(m_ErasePawn, IMG(imgColor + QUEEN));
						break;
					default:
						return false;
					}

					//delete m_ErasePawn;
					//m_Pieces[campColor][j] = newPiece;

					return true;
				}
			}
		}
	}
	return false;
}

void PiecesManager::DrawPawnPromotion(HDC hdc_SubPromotion)
{
	//std::wstring str;
	std::string str;
	//HFONT font = CreateFont(PROMOTION_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	HFONT font = CreateFont(PROMOTION_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, "Times New Roman");


	//글자 크기 변경
	SelectObject(hdc_SubPromotion, font);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc_SubPromotion, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc_SubPromotion, RGB(255, 255, 255)); //글자 색 변경(흰색)
	//SetTextColor(hdc_SubPromotion, RGB(128, 128, 128)); //글자 색 변경(회색)

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		switch (m_promotionRect[i].top)
		{
		case PROMOTION_ROOK_T:
			str = "R o o k";
			break;
		case PROMOTION_KNIGHT_T:
			str = "K n i g h t";
			break;
		case PROMOTION_BISHOP_T:
			str = "B i s h o p";
			break;
		case PROMOTION_QUEEN_T:
			str = "Q u e e n";
			break;
		}

		//DrawText(hdc_SubPromotion, str.c_str(), -1, &m_promotionRect[i], DT_CENTER | DT_WORDBREAK);
		DrawText(hdc_SubPromotion, (LPCSTR)str.c_str(), -1, &m_promotionRect[i], DT_CENTER | DT_WORDBREAK);
	}
}

void PiecesManager::MovingObject_Does_ErasePiece(int _campColor, int _piece)
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
						GMMgr->Set_IsWinCheck(true);
						//GMMgr->Set_GameStopCheck(true);
						//GMMgr->Set_GameEndCheck(true);
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
			m_Pieces[campColor][piece]->Draw(hdc);
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



//-- Chess Network ----

void PiecesManager::MovePiece_FromServer(int _x, int _y, RECT _moveRect)
{
	//x,y가 움직이기 전 map의 인덱스
	//rect가 이동한 후의 위치

	//map 인덱스로 해당 말을 찾는다.
	Piece* pieceTmp;

	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			pieceTmp = m_Pieces[campColor][piece];

			if ((pieceTmp->Get_iX() == _x) && (pieceTmp->Get_iY() == _y))
			{
				//현재 이동한 말의 좌표가 상대 진영 끝줄에 닿아서 ErasePawn을 세팅할 경우
				if (GMMgr->Get_IsPromotion())
					m_ErasePawn = pieceTmp;


				//해당 말의 m_moveRect를 갱신
				pieceTmp->Set_moveRect(_moveRect);

				
				//클라이언트에저 전부 동시에 뿌려져야 말이 잡히는 게 구현이 된다.
				//적 기물을 먹는 경우 + 킹 게임오버 체크 //endCheck와 stopCheck를 조정한다.
				MovingObject_Does_ErasePiece(campColor, piece); //현재 움직이는 말의 정보
				
				
				//이동
				pieceTmp->Move();
				return;
			}
		}
	}

	//PieceErase()에서 게임 종료 확인 했음
	//if (GMMgr->Get_GameEndCheck())
	//	return true;

	//Pawn이 상대측 y축 끝까지 도달 > 승진 진행(킹을 잡은 경우 제외
	if (PawnPromotionCheck(pieceTmp))
	{
	//	//승진중에 입력 막기
	//	GMMgr->Set_GameStopCheck(true);
		m_ErasePawn = pieceTmp;
	//	//GMMgr->Set_PlayerTurn();
	//	//상태 턴 대기
	//	GMMgr->SetDelayTurn();
		InvalidateRect(GMMgr->Get_HWND_Sub_Promotion(), NULL, false);
	}

	//이동 가능한 위치로 옮기려 하는지 체크
	if (GMMgr->Get_GameStopCheck() == false)
	{
		//상태 턴 대기
		GMMgr->SetDelayTurn();


		//현재 턴과 반대되는 턴을 세팅해준다.(플레이어 턴 전환)
		//GMMgr->Set_PlayerTurn();
	}


	//sub Window 색상 변경 위해
	InvalidateRect(GMMgr->Get_HWND_Sub(), NULL, false);
}


bool PiecesManager::IsDataMoveEnd(CAMP team, int y)
{
	//Pawn이 상대측 y축 끝까지 도달 > 승진
	switch (team)
	{
	case CAMP_BLACK:
		if (y == WHITE_END_Y)
			return true;
		break;
	case CAMP_WHITE:
		if (y == BLACK_END_Y)
			return true;
		break;
	}


	return false;
}

void PiecesManager::Promotion(PROMOTION_RECT _PromotionType)
{
	this->m_PromotionType = _PromotionType;

	Piece* newPiece = { };
	CAMP campColor = m_ErasePawn->Get_CampColor();
	//이미지 B W 구분 설정을 위해 
	IMG imgColor = (IMG)(campColor == CAMP_BLACK) ? IMG_BLACK_START : IMG_WHITE_START;


	switch (m_PromotionType)
	{
	case PROMOTION_ROOK_T:
		newPiece = new Rook(m_ErasePawn, IMG(imgColor + ROOK));
		break;
	case PROMOTION_KNIGHT_T:
		newPiece = new Knight(m_ErasePawn, IMG(imgColor + KNIGHT));
		break;
	case PROMOTION_BISHOP_T:
		newPiece = new Bishop(m_ErasePawn, IMG(imgColor + BISHOP));
		break;
	case PROMOTION_QUEEN_T:
		newPiece = new Queen(m_ErasePawn, IMG(imgColor + QUEEN));
		break;
	default:
		break;
	}

	for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
	{
		if (m_ErasePawn == m_Pieces[campColor][piece])
		{
			m_Pieces[campColor][piece] = newPiece;
			break;
		}
	}
	delete m_ErasePawn;
}
