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
	//��
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

	//��
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

	////����Ʈ
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

	////���
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

	////��
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


	////ŷ
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
	for (int campColor = 0; campColor < CAMP_COUNT; campColor++)
	{
		for (int piece = 0; piece < CAMP_PIECE_COUNT; piece++)
		{
			if (m_MoveTurn == false)
			{//�̵� ���� �̹��� �ݶ��̴� rect ����(�� Ŭ�� �� ���� �� �̵� �����ع����� �ȵǹǷ�)
				if (m_Pieces[campColor][piece]->ColliderCheck_Piece(point))
				{//�⹰ �̵� Ŭ��
					m_MoveTurn = true;
					return true;
				}
			}
			else
			{
				if (m_Pieces[campColor][piece]->ColliderCheck_Moveable(point))
				{//�̵� movealbe Ŭ��
					m_MoveTurn = false;

					//�� �⹰�� �Դ� ���
					PieceErase(campColor, piece);

					//XY ��ǥ�� Rect �̵�
					m_Pieces[campColor][piece]->Move();

					if (GMMgr->Get_GameEndCheck() == false)
						//���� �ϰ� �ݴ�Ǵ� ���� �������ش�.(�÷��̾� �� ��ȯ)
					GMMgr->Set_PlayerTurn();

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

void PiecesManager::PieceErase(int _campColor, int _piece)
{//TODO::�� �⹰�� �Դ� ���

	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();
	IMG IMG_PieceType;

	//Ư�� ��ġ�� �̵��� �⹰
	RECT moveRect = m_Pieces[_campColor][_piece]->Get_moveRect();
	CAMP moveCampColor = m_Pieces[_campColor][_piece]->Get_CampColor();

	//moveRect�� Piece�� �̵��� ��ġ�� �ִ� �⹰
	RECT bitmapRect;
	CAMP bitmapCampColor = map[moveRect.left / IMG_BG_SIZE][moveRect.top / IMG_BG_SIZE];


	if (bitmapCampColor != CAMP_NONE &&
		bitmapCampColor != moveCampColor)
	{
		//m_Pieces �����鼭 ��ġ�� ���� �ִ��� Ȯ��
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

					//���� �¸� üũ
					//ŷ���� üũ ����
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
