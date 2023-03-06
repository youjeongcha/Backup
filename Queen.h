#pragma once
#include "Piece.h"

class Queen : public Piece
{
private:

public:
	Queen();
	Queen(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y);
	~Queen();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};

