#pragma once
#include "Piece.h"

enum PAWN
{
	MAX_MOVE_COUNT = 2,

	//Pawn�� ���� �Դ� ����
	EAT_LEFT = 0,
	EAT_RIGHT = 1,

	//Pawn�� �� ������ �� ���� ������ ���
	BLACK_END_Y = 0,
	WHITE_END_Y = 7,
};

class Pawn : public Piece
{
private:
public:
	Pawn();
	//Pawn(Piece _piece);
	Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y); //�θ��� �����ڸ� ���.cpp����
	~Pawn();

	//virtual bool ColliderCheck_Piece(POINT point) override;
	//virtual bool ColliderCheck_CanMove(POINT point) override;
	virtual void SetMoveableRect() override;
};