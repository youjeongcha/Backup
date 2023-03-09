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
	//int black_Y = 1; //�渻 ������ �� ���� y index
	//int next_Y; //�� ������ ��Ī�̶� y�� ������ �޶�� �Ѵ�.
	//int oneLinePieces = CAMP_PIECE_COUNT / 2; //���ٿ� �� �� �ִ� ���� ���� 8
	//int halfLinePieces = oneLinePieces / 2; //������ ���� �� ���� 4
	//int x_Symmetry = 7; //�¿� ��Ī Ȯ�� ���� x�� ��Ī�� ��
	//int y_Pawn_Gap = 5; //��� �� Pawn�� y��ǥ ���̰�
	//int y_Pawn_Gap = 7; //��� �� Pawn ���� y��ǥ ���̰�
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

	//���� �ִ� �� > �ٸ� ���� �� ���� �ʱ�ȭ

	//��
	for (int x = 0; x <= ONELINE_PIECES_COUNT; x++) //���� �������� x���� id number
	{
		//tmpPiece = new Pawn(*BitMapMgr_Main, campColor, pieceIndex, x, y);
		m_Pieces[CAMP_BLACK][pieceCount] = new Pawn(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_PAWN, x, BLACK_PAWN_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Pawn(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_PAWN, x, WHITE_PAWN_Y);
		//m_Pieces[campColor][pieceCount++]->Init(BitMapMgr_Main, campColor, pieceIndex, x, y);
	}

	//y += next_Y;

	//pieceIndex = (IMG)(pieceIndex + 1);
	
	//MakePiece<Rook>(BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);


	//��*2
	//for (int x = 0; x < PIECES_ROOK; x++) //���� �������� x���� id number
	{
		m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Rook(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_ROOK, FIRST_ROOK_X, WHITE_OTHER_Y);

		m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, SECOND_ROOK_X, BLACK_OTHER_Y);
		m_Pieces[CAMP_WHITE][pieceCount++] = new Rook(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_ROOK, SECOND_ROOK_X, WHITE_OTHER_Y);
	}

	//����Ʈ*2
	m_Pieces[CAMP_BLACK][pieceCount] = new Knight(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KNIGHT, FIRST_KNIGHT_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Knight(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KNIGHT, FIRST_KNIGHT_X, WHITE_OTHER_Y);


	m_Pieces[CAMP_BLACK][pieceCount] = new Knight(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KNIGHT, SECOND_KNIGHT_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Knight(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KNIGHT, SECOND_KNIGHT_X, WHITE_OTHER_Y);

	//���*2
	m_Pieces[CAMP_BLACK][pieceCount] = new Bishop(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_BISHOP, FIRST_BISHOP_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Bishop(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_BISHOP, FIRST_BISHOP_X, WHITE_OTHER_Y);

	m_Pieces[CAMP_BLACK][pieceCount] = new Bishop(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_BISHOP, SECOND_BISHOP_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Bishop(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_BISHOP, SECOND_BISHOP_X, WHITE_OTHER_Y);

	//��
	m_Pieces[CAMP_BLACK][pieceCount] = new Queen(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_QUEEN, QUEEN_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new Queen(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_QUEEN, QUEEN_X, WHITE_OTHER_Y);

	//ŷ
	m_Pieces[CAMP_BLACK][pieceCount] = new King(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_KING, KING_X, BLACK_OTHER_Y);
	m_Pieces[CAMP_WHITE][pieceCount++] = new King(*BitMapMgr_Main, CAMP_WHITE, IMG_WHITE_KING, KING_X, WHITE_OTHER_Y);

	//for (int x = 0; x < HALFLINE_PIECES_COUNT; x++)
	//{
	//	//��Ī�Ǵ� ���� �� ����(��, ����Ʈ, ���)
	//	//m_Pieces[CAMP_BLACK][pieceCount] = new Rook(*BitMapMgr_Main, CAMP_BLACK, IMG_BLACK_ROOK, FIRST_ROOK_X, BLACK_OTHER_Y);
	//	//Piece tmpPiece1 = Piece(*BitMapMgr_Main, campColor, pieceIndex, x, y);
	//	//m_Pieces[campColor][pieceCount++] = &tmpPiece1;
	//	//m_Pieces[campColor][pieceCount++]->Init(BitMapMgr_Main, campColor, pieceIndex, x, y);

	//	if (x == PIECES::PIECES_QUEEN - 1) //���� ŷ�� �ٸ��� ���� �ʿ�
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

			//�⹰ Ŭ��
			if (m_MoveTurn == false)
			{//�̵� ���� �̹��� �ݶ��̴� rect ����(�� Ŭ�� �� ���� �� �̵� �����ع����� �ȵǹǷ�)
				if (pieceTmp->ColliderCheck_Piece(point))
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

					//�� �⹰�� �Դ� ���
					PieceErase(campColor, piece); //���� �����̴� ���� ����

					//XY ��ǥ�� Rect �̵�
					pieceTmp->Move();


					//Pawn�� ����� y�� ������ ���� > ���� ����
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

void PiecesManager::PieceErase(int _campColor, int _piece)
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
