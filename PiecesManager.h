#pragma once
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"


enum PIECES
{
	PAWN = 0,
	//promotion~
	ROOK = 1,
	KNIGHT,
	BISHOP,
	QUEEN,
	//~promotion
	KING,
	PROMOTION_COUNT = QUEEN,
};

enum PROMOTION_RECT
{
	PROMOTION_RECT_L = 0,
	PROMOTION_RECT_T = 25,
	PROMOTION_RECT_R = PROMOTION_RECT_L + 120,
	PROMOTION_RECT_B = PROMOTION_RECT_T + 30,

	PROMOTION_RECT_GAP = 30,


	PROMOTION_ROOK_T = PROMOTION_RECT_T,
	PROMOTION_KNIGHT_T = PROMOTION_ROOK_T + PROMOTION_RECT_GAP,
	PROMOTION_BISHOP_T = PROMOTION_KNIGHT_T + PROMOTION_RECT_GAP,
	PROMOTION_QUEEN_T = PROMOTION_BISHOP_T + PROMOTION_RECT_GAP,

	PROMOTION_FONTSIZE = 11,
};

enum PIECES_COUNT
{
	PIECES_PAWN = 8,
	PIECES_ROOK = 2,
	PIECES_KNIGHT = 2,
	PIECES_BISHOP = 2,
	PIECES_QUEEN = 1,
	PIECES_KING = 1,
};

enum PIECE_XY_ID//m_Pieces�� �⹰ xy��ǥ
{
	BLACK_PAWN_Y = 1,
	BLACK_OTHER_Y = 0,

	WHITE_PAWN_Y = 6,
	WHITE_OTHER_Y = 7,

	ONELINE_PIECES_COUNT = CAMP_PIECE_COUNT / 2 - 1,
	
	HALFLINE_PIECES_COUNT = ONELINE_PIECES_COUNT / 2 + 1,

	FIRST_PAWN_X = 0,
	FIRST_ROOK_X = 0,
	SECOND_ROOK_X = ONELINE_PIECES_COUNT - FIRST_ROOK_X,
	FIRST_KNIGHT_X = 1,
	SECOND_KNIGHT_X = ONELINE_PIECES_COUNT - FIRST_KNIGHT_X,
	FIRST_BISHOP_X = 2,
	SECOND_BISHOP_X = ONELINE_PIECES_COUNT - FIRST_BISHOP_X,
	QUEEN_X = 3,
	KING_X = 4,
};

class PiecesManager
{
private:
	static PiecesManager* m_pInstance;
	//BitMapManager* BitMapMgr_Main;
	Piece* m_Pieces[CAMP_COUNT][CAMP_PIECE_COUNT];
	bool m_MoveTurn;//�̵� ���� �̹��� �ݶ��̴� ���� ��(�� Ŭ�� �� ���� �� �̵� �����ع����� �ȵǹǷ�)
	RECT m_promotionRect[PROMOTION_COUNT];
	Piece* m_ErasePawn;

	void InitLocation(BitMapManager* BitMapMgr_Main);
	//���ڴ� ���� �����̴� ���� ������ �޾Ƽ� ���� ����� ã�´�.
	void MovingObject_Does_ErasePiece(int _campColor, int _piece); //�ڸ�Ī ����(�˾ƺ��� ���� ������)
	bool PawnPromotionCheck(Piece* pieceTmp);
	

	PiecesManager();

public:
	~PiecesManager();
	
	static PiecesManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new PiecesManager;
		return m_pInstance;
	}

	void Init(BitMapManager* BitMapMgr_Main);
	//���� window
	bool ColliderCheck(POINT point);
	void DrawPices(HDC hdc);
	//���� window
	bool ColliderCheck_SubPromotion(POINT point);
	void DrawPawnPromotion(HDC hdc_SubPromotion);

	//�ݶ��̴� üũ ��, ������ ������ ĭ �����ֱ�
	void DrawMoveable(HDC hdc);
};

