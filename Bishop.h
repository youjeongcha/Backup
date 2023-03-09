#pragma once
#include "Piece.h"

class Bishop : public Piece
{
private:

public:
	Bishop(Piece _piece, IMG _Index);
	Bishop(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //부모의 생성자를 상속.cpp참고
	~Bishop();

	virtual void SetMoveableRect() override;
};

