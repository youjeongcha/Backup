#pragma once
#include "Piece.h"

class Knight : public Piece
{
private:

public:
	Knight();
	Knight(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Knight();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};

