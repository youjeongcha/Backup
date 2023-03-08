#pragma once
#include "Piece.h"

enum PAWN
{
	MAX_MOVE_COUNT = 2,

	//Pawn이 말을 먹는 방향
	EAT_LEFT = 0,
	EAT_RIGHT = 1,

	//Pawn이 적 진영의 맨 끝에 도달한 경우
	BLACK_END_Y = 0,
	WHITE_END_Y = 7,
};

class Pawn : public Piece
{
private:
public:
	Pawn();
	//Pawn(Piece _piece);
	Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //부모의 생성자를 상속.cpp참고
	~Pawn();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};