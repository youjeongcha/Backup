#pragma once
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"


enum PROMOTION_PIECES
{
	PROMOTION_ROOK = 1,
	PROMOTION_KNIGHT,
	PROMOTION_BISHOP,
	PROMOTION_QUEEN,
	PROMOTION_COUNT = PROMOTION_QUEEN,
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

enum PIECE_XY_ID
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

	void InitLoaction(BitMapManager* BitMapMgr_Main);
	void PieceErase(int _campColor, int _piece);
	bool PawnPromotionCheck(Piece* pieceTmp);
	
	template<typename TPieces, typename = std::enable_if<std::is_base_of<Piece, TPieces>::value>>
	std::vector<Piece*> MakePieces(BitMapManager* _BitMapMgr, IMG _pieceID, int _X, int _Y, int _count)
	//std::vector<std::vector<TPieces*>> MakePieces(BitMapManager* BitMapMgr, CAMP campColor, IMG pieceID, int x, int y)
	//std::vector<std::vector<TPieces*>> MakePieces(BitMapManager* BitMapMgr)
	{//�������� �ޱ�
		std::vector<Piece*> piecesList;
		//int pieceCount = 0;
		//IMG pieceIndex;

		switch (_pieceID)
		{
		case IMG_BLACK_PAWN: //��
			for (int x = 0; x < _count; x++) //���� �������� x���� id number
			{
				//���� �⹰
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, _X + x, _Y));
				//�� �⹰
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_WHITE, _pieceID + IMG_BLACK_COUNT, _X + x, _Y + 5)); //gap TODO
			}
			break;
		case IMG_BLACK_QUEEN: //��
		case IMG_BLACK_KING: //ŷ
			//���� �⹰
			piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, _X, _Y));
			//�� �⹰
			piecesList.push_back(new TPieces(_BitMapMgr, CAMP_WHITE, _pieceID + IMG_BLACK_COUNT, _X, _Y + 7)); //gap TODO
			break;
		default: //��, ����Ʈ, ���
			for (int x = 0; x < _count; x++) //���� �������� x���� id number
			{
				//���� �⹰
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, abs(ONELINE_PIECES_COUNT * x - _X), _Y));
				//�� �⹰
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_WHITE, _pieceID + IMG_BLACK_COUNT, abs(ONELINE_PIECES_COUNT * x - _X), _Y + 7)); //gap TODO
			}
			break;
		}

		return piecesList;
	}

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

