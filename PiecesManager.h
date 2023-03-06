#pragma once
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

//enum PIECES
//{
//	PIECES_PAWN,
//	PIECES_ROOK,
//	PIECES_KNIGHT,
//	PIECES_BISHOP,
//	PIECES_QUEEN,
//	PIECES_KING,
//};

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
	bool m_MoveTurn;//이동 가능 이미지 콜라이더 적용 턴(말 클릭 안 했을 시 이동 가능해버리면 안되므로)

	void InitLoaction(BitMapManager* BitMapMgr_Main);
	void PieceErase(int _campColor, int _piece);
	
	template<typename TPieces>
	std::vector<Piece*> MakePieces(BitMapManager* _BitMapMgr, IMG _pieceID, int _X, int _Y, int _count)
	//std::vector<std::vector<TPieces*>> MakePieces(BitMapManager* BitMapMgr, CAMP campColor, IMG pieceID, int x, int y)
	//std::vector<std::vector<TPieces*>> MakePieces(BitMapManager* BitMapMgr)
	{//종류별로 받기
		std::vector<Piece*> piecesList;
		//int pieceCount = 0;
		//IMG pieceIndex;

		switch (_pieceID)
		{
		case IMG_BLACK_PAWN: //폰
			for (int x = 0; x < _count; x++) //말의 개수이자 x축의 id number
			{
				//검은 기물
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, _X + x, _Y));
				//흰 기물
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_WHITE, _pieceID + IMG_BLACK_COUNT, _X + x, _Y + 5)); //gap TODO
			}
			break;
		case IMG_BLACK_QUEEN: //퀸
		case IMG_BLACK_KING: //킹
			//검은 기물
			piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, _X, _Y));
			//흰 기물
			piecesList.push_back(new TPieces(_BitMapMgr, CAMP_WHITE, _pieceID + IMG_BLACK_COUNT, _X, _Y + 7)); //gap TODO
			break;
		default: //룩, 나이트, 비숍
			for (int x = 0; x < _count; x++) //말의 개수이자 x축의 id number
			{
				//검은 기물
				piecesList.push_back(new TPieces(_BitMapMgr, CAMP_BLACK, _pieceID, abs(ONELINE_PIECES_COUNT * x - _X), _Y));
				//흰 기물
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
	bool ColliderCheck(POINT point);
	void DrawPices(HDC hdc);
	//콜라이더 체크 후, 움직임 가능한 칸 보여주기
	void DrawMoveable(HDC hdc);

	//void Set_Piece_InativeXY(int _campColor, int _piece) { m_Pieces[_campColor][_piece]->Set_XY(-1, -1); }
};

