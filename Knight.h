#pragma once
#include "Piece.h"

class Knight : public Piece
{
private:

public:
	Knight(Piece _piece, IMG _Index);
	Knight(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Knight();

	virtual void SetMoveableRect() override;
};

