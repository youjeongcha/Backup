#pragma once
#include "Piece.h"

class Queen : public Piece
{
private:

public:
	Queen(Piece* _piece, IMG _Index);
	Queen(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y);
	~Queen();

	virtual void SetMoveableRect() override;
};

