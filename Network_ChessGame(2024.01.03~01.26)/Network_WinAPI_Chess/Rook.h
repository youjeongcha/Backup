#pragma once
#include "Piece.h"

class Rook : public Piece
{
private:

public:
	Rook(Piece* _piece, IMG _Index);
	Rook(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Rook();

	virtual void SetMoveableRect() override;
};

