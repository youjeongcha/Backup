#pragma once
#include "Piece.h"

class Bishop : public Piece
{
private:

public:
	Bishop(Piece _piece, IMG _Index);
	Bishop(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Bishop();

	virtual void SetMoveableRect() override;
};

