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
	IMG pieceIndex;
	int imgColor;
	int colorPiece_Pawn_Y, colorPiece_Other_Y;

	//���� �ִ� �� > �ٸ� ���� �� ���� �ʱ�ȭ

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

		//��*8 //�ڻ��� ������ �� ���´� enum�� ���� �ٶ�
		for (int x = 0; x < PIECES_PAWN; x++) //���� �������� x���� id number
			m_Pieces[camp][pieceCount++] = new Pawn(*BitMapMgr_Main, (CAMP)camp, (IMG)(PAWN + imgColor), x, colorPiece_Pawn_Y);

		//��*2
		m_Pieces[camp][pieceCount++] = new Rook(*BitMapMgr_Main, (CAMP)camp, (IMG)(ROOK + imgColor), FIRST_ROOK_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Rook(*BitMapMgr_Main, (CAMP)camp, (IMG)(ROOK + imgColor), SECOND_ROOK_X, colorPiece_Other_Y);

		//����Ʈ*2
		m_Pieces[camp][pieceCount++] = new Knight(*BitMapMgr_Main, (CAMP)camp, (IMG)(KNIGHT + imgColor), FIRST_KNIGHT_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Knight(*BitMapMgr_Main, (CAMP)camp, (IMG)(KNIGHT + imgColor), SECOND_KNIGHT_X, colorPiece_Other_Y);

		//���*2
		m_Pieces[camp][pieceCount++] = new Bishop(*BitMapMgr_Main, (CAMP)camp, (IMG)(BISHOP + imgColor), FIRST_BISHOP_X, colorPiece_Other_Y);
		m_Pieces[camp][pieceCount++] = new Bishop(*BitMapMgr_Main, (CAMP)camp, (IMG)(BISHOP + imgColor), SECOND_BISHOP_X, colorPiece_Other_Y);

		//��
		m_Pieces[camp][pieceCount++] = new Queen(*BitMapMgr_Main, (CAMP)camp, (IMG)(QUEEN + imgColor), QUEEN_X, colorPiece_Other_Y);

		//ŷ
		m_Pieces[camp][pieceCount++] = new King(*BitMapMgr_Main, (CAMP)camp, (IMG)(KING + imgColor), KING_X, colorPiece_Other_Y);
	}
}

bool PiecesManager::ColliderCheck(POINT point)
{//�ڹݺ����� �� ���ƾ� �ϴ� ������ ������ ���� ������ ���ݿͼ� ��ġ�⿡�� �ڵ带 �� �����ľ� �Ѵ�. ������ ���� �ٶ�
	Piece* pieceTmp;

	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			pieceTmp = m_Pieces[campColor][piece];

			//�⹰ Ŭ��
			if (m_MoveTurn == false)
			{//�̵� ���� �̹��� �ݶ��̴� rect ����(�� Ŭ�� �� ���� �� �̵� �����ع����� �ȵǹǷ�)
				if ((GMMgr->Get_PlayerTurn() == pieceTmp->Get_CampColor()) && (pieceTmp->ColliderCheck_Piece(point)))
				{//�⹰ �̵� Ŭ��
					m_MoveTurn = true;
					return true;
				}
			}
			else
			{//�⹰�� moveable Ŭ��
				if (pieceTmp->ColliderCheck_Moveable(point))
				{//�̵� movealbe Ŭ��
					m_MoveTurn = false;

					//�� �⹰�� �Դ� ��� + ŷ ���ӿ��� üũ //endCheck�� stopCheck�� �����Ѵ�.
					MovingObject_Does_ErasePiece(campColor, piece); //���� �����̴� ���� ����

					//XY ��ǥ�� Rect �̵� //�ð������� ��Ÿ���ֱ� �� ���� �̵����� �⹰�� ��ǥ�� �̵�
					pieceTmp->Move();

					//PieceErase()���� ���� ���� Ȯ�� ����
					if (GMMgr->Get_GameEndCheck())
						return true;

					//Pawn�� ����� y�� ������ ���� > ���� ����(ŷ�� ���� ��� ����
					if (PawnPromotionCheck(pieceTmp))
					{
						//�����߿� �Է� ����
						GMMgr->Set_GameStopCheck(true);
						m_ErasePawn = pieceTmp;
						GMMgr->Set_PlayerTurn();
						InvalidateRect(GMMgr->Get_HWND_Sub_Promotion(), NULL, true);
					}

					if (GMMgr->Get_GameStopCheck() == false)
					{
						//���� �ϰ� �ݴ�Ǵ� ���� �������ش�.(�÷��̾� �� ��ȯ)
						GMMgr->Set_PlayerTurn();
					}


					//sub Window ���� ���� ����
					InvalidateRect(GMMgr->Get_HWND_Sub(), NULL, true);

					return true;
				}
			}
		}
	}

	//�ʱ�ȭ �ʿ�
	//�̵����� �ʰ� �̵� ���� rect ���� Ŭ���� ��� : �ش� �� �̵� ���
	if (m_MoveTurn)
	{
		m_MoveTurn = false;
		return true;
	}

	return false;
}

bool PiecesManager::PawnPromotionCheck(Piece* pieceTmp)
{
	//Pawn�� ����� y�� ������ ���� > ����
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
	//�̹��� B W ���� ������ ���� 
	IMG imgColor = (IMG)(campColor == CAMP_BLACK) ? IMG_BLACK_START : IMG_WHITE_START;

	for (int i = 0; i < PROMOTION_COUNT; i++)
	{
		if (PtInRect(&m_promotionRect[i], point)) //���� �������� �� ���
		{
			//�� �⹰�� �־��־�� �ϱ� ������ �ּҸ� ã�� ���ؼ�
			for (int j = 0; j < CAMP_PIECE_COUNT; j++)
			{
				if (m_ErasePawn == m_Pieces[campColor][j])
				{
					switch (m_promotionRect[i].top)
					{
					case PROMOTION_ROOK_T:
						newPiece = new Rook(*m_ErasePawn, IMG(imgColor + ROOK));
						break;
					case PROMOTION_KNIGHT_T:
						newPiece = new Knight(*m_ErasePawn, IMG(imgColor + KNIGHT));
						break;
					case PROMOTION_BISHOP_T:
						newPiece = new Bishop(*m_ErasePawn, IMG(imgColor + BISHOP));
						break;
					case PROMOTION_QUEEN_T:
						newPiece = new Queen(*m_ErasePawn, IMG(imgColor + QUEEN));
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


	//���� ũ�� ����
	SelectObject(hdc_SubPromotion, font);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc_SubPromotion, TRANSPARENT); //���� �޹�� ����ȭ
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc_SubPromotion, RGB(255, 255, 255)); //���� �� ����

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

void PiecesManager::MovingObject_Does_ErasePiece(int _campColor, int _piece)
{//�� �⹰�� �Դ� ��� //���� �����̴� ���� ����

	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//Ư�� ��ġ�� �̵��� �⹰
	Piece* movePiece = m_Pieces[_campColor][_piece];
	RECT moveRect = movePiece->Get_moveRect();
	//CAMP moveCampColor = movePiece->Get_CampColor();

	//moveRect�� Piece�� �̵��� ��ġ�� �ִ� �⹰
	RECT delete_BitmapRect;
	CAMP delete_bitmapCampColor = map[moveRect.left / IMG_BG_SIZE][moveRect.top / IMG_BG_SIZE];
	//������ �⹰�� ���� üũ ����
	IMG delete_IMG_PieceType;

	//���Ļ�� : moveRect�� Piece�� �̵��� ��ġ�� �ִ� �⹰
	//IMG movePieceType = movePiece->Get_PieceType();


	if ((delete_bitmapCampColor != CAMP_NONE) &&
		(delete_bitmapCampColor != movePiece->Get_CampColor()))
	{
		//m_Pieces �����鼭 ��ġ�� ���� �ִ��� Ȯ��
		for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
		{
			for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
			{
				//moveCampColor = m_Pieces[campColor][piece]->Get_CampColor();
				delete_BitmapRect = m_Pieces[campColor][piece]->Get_BitMapRect();

				//���� ŷ�� üũ ����
				//delete_IMG_PieceType = m_Pieces[campColor][piece]->Get_PieceType();


				////���Ļ�
				////�����̰� �ִ� PAWN
				//switch (movePieceType)
				//{
				//case IMG_BLACK_PAWN :
				//	//TODO::��ǥ ��밡 ������ 2ĭ ������ ������ Ȯ��(2ĭ!)
				//	if (delete_IMG_PieceType == IMG_WHITE_PAWN)
				//	{
				//		m_Pieces[campColor][piece].
				//	}
				//	break;
				//case IMG_WHITE_PAWN:
				//	//TODO::��ǥ ��밡 ������ 2ĭ ������ ������ Ȯ��(2ĭ!)
				//	if (delete_IMG_PieceType == IMG_BLACK_PAWN)
				//	{
				//	}
				//	break;
				//default:
				//	break;
				//}


				//�Ϲ����� movableRect�� ������ ���� ��ġ�� ���
				if ((delete_BitmapRect.left == moveRect.left) && (delete_BitmapRect.top == moveRect.top))
				{
					//GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);
					//�⹰�� �þ߿��� ����� ��Ȱ��ȭ
					m_Pieces[campColor][piece]->Set_Inactive();

					//���� �¸� üũ
					//ŷ���� üũ ����
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
			m_Pieces[campColor][piece]->Draw(hdc);
	}
}

void PiecesManager::DrawMoveable(HDC hdc)
{
	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			//�̵� ǥ�� üũ ��û�� ���Դ���
			if (m_Pieces[campColor][piece]->Get_MoveCheck())
			{
				m_Pieces[campColor][piece]->SetMoveableRect();
				m_Pieces[campColor][piece]->DrawMoveable(hdc);
				return;
			}
		}
	}
}
