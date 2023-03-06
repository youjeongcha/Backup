#pragma once
#include "Piece.h"

enum PAWN
{
	MAX_MOVE_COUNT = 2,

	EAT_LEFT = 0,
	EAT_RIGHT = 1,

};

class Pawn : public Piece
{
private:
public:
	Pawn();
	Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //부모의 생성자를 상속.cpp참고
	~Pawn();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};