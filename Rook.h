#pragma once
#include "Piece.h"

//enum ROOK
//{
//	MAX_MOVE_COUNT = 4,
//
//	EAT_LEFT = 0,
//	EAT_RIGHT = 1,
//
//};

class Rook : public Piece
{
private:

public:
	Rook();
	Rook(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Rook();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};

