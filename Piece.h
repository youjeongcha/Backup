#pragma once
#include "BitMapManager.h"
#include <vector>

enum ONELINE_MAXCOUNT
{//한 방향에서 가지는 최대 Rect 수
	PAWN_LINE_COUNT = 1, //전방 + 대각선
	PAWN_LINE_MAX_COUNT = 2, //첫번째 전방 이동
	ROOK_LINE_COUNT = 7, //한 줄 7(현재 위치 제외)
	KNIGHT_LINE_COUNT = 1, //동남, 동북, 서남, 서북, 북동, 북서, 남동, 남서 1개씩
	BISHOP_LINE_COUNT = 7, //대각선 최대 7
	QUEEN_LINE_COUNT = 7, //직선과 대각선 고려 7
	KING_LINE_COUNT = 1, //자기 주변 1
};

enum CAMP
{
	CAMP_NONE = -1,
	CAMP_BLACK,
	CAMP_WHITE,
	CAMP_COUNT,

	CAMP_PIECE_COUNT = 16,
};

class Piece
{
private:
protected: //private 으로 하면 자식에서 접근 불가 > protected
	BitMap* m_pBitMap;
	BitMap* m_pBitMap_Move; //이동 표시
	bool m_moveCheck; //이동 표시 체크 요청이 들어왔는지
	RECT m_BitMapRect;
	RECT m_moveRect; //이동 시킬 rect 임시 저장용
	std::vector<RECT> m_BitMapRect_MoveList;
	int m_iX; //map에서의 인덱스
	int m_iY;
	int move_iY;
	IMG m_Piece; //해당 기물의 enum;
	CAMP m_CampColor; //해당 기물의 진영
	bool firstMoveCheck; //첫번째 이동인지 확인

public:
	Piece();
	//Piece(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y);
	Piece(BitMapManager& BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y);
	~Piece();

	//void Init(BitMapManager* BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y);
	//이동 가능한 칸을 나타낸 이미지를 클릭한 경우
	bool ColliderCheck_Piece(POINT point);
	bool ColliderCheck_Moveable(POINT point);
	//bool ColliderCheck_Move(POINT point);
	//virtual bool ColliderCheck_Piece(POINT point);
	//virtual bool ColliderCheck_CanMove(POINT point);
	//이동 가능한 칸들을 그린다.
	//virtual void DrawMoveable(HDC hdc);
	virtual void SetMoveableRect();
	void DrawMoveable(HDC hdc);
	//기물의 실제 이동
	void Move();
	void Draw(HDC hdc);
	//void DrawMovealbe(HDC hdc);

	//void Set_Rect(RECT _rect);
	void Set_XY(int _X, int _Y) { m_iX = _X; m_iY = _Y; }
	void Set_Inactive() {
		m_iX = -1; m_iY = -1; //화면상 뜨지 않도록
		m_BitMapRect = { -1, -1, -1, -1 }; //클릭 colliderCheck 인식X하도록
	}
	//상하좌우 중 한 케이스의 Rect를  m_BitMapRect_MoveList에 push
	void Set_Rect(CAMP map[][8], int move_iX, int move_iY, int count);

	bool Get_MoveCheck() { return m_moveCheck; }
	RECT Get_moveRect() { return m_moveRect; } //적 말 먹을때 위치 파악
	RECT Get_BitMapRect() { return m_BitMapRect; } //적 말 먹을때 위치 파악
	CAMP Get_CampColor() { return m_CampColor; }
	//void Set_MoveCheck(bool _moveCheck) { m_moveCheck = _moveCheck; }
};

