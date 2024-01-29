#pragma once
#include "Piece.h"

enum PAWN
{
	MAX_MOVE_COUNT = 2,
	ENPASSANT_CHECK = 1,

	//Pawn�� ���� �Դ� ����
	EAT_LEFT = 0,
	EAT_RIGHT,
	ENPASSANT_LEFT,
	ENPASSANT_RIGHT,

	//Pawn�� �� ������ �� ���� ������ ���
	BLACK_END_Y = 0,
	WHITE_END_Y = 7,
};

class Pawn : public Piece
{
public:
	Pawn(Piece* _piece, IMG _Index); //������ ���ؼ� �� �̴ϼȶ������� ������� �ʴ´�.
	Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, int _X, int _Y); //�θ��� �����ڸ� ���.cpp����
	~Pawn();

	virtual void SetMoveableRect() override;
};