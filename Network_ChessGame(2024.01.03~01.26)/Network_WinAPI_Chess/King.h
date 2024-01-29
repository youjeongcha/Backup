#pragma once
#include "Piece.h"

class King : public Piece
{
private:

public:
	King(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //부모의 생성자를 상속.cpp참고
	~King();

	virtual void SetMoveableRect() override;
};

