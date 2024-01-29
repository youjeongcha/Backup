#pragma once
#include "Piece.h"

enum PAWN
{
	MAX_MOVE_COUNT = 2,
	ENPASSANT_CHECK = 1,

	//Pawn이 말을 먹는 방향
	EAT_LEFT = 0,
	EAT_RIGHT,
	ENPASSANT_LEFT,
	ENPASSANT_RIGHT,

	//Pawn이 적 진영의 맨 끝에 도달한 경우
	BLACK_END_Y = 0,
	WHITE_END_Y = 7,
};

class Pawn : public Piece
{
public:
	Pawn(Piece* _piece, IMG _Index); //승진을 위해서 이 이니셜라이저는 사용하지 않는다.
	Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, int _X, int _Y); //부모의 생성자를 상속.cpp참고
	~Pawn();

	virtual void SetMoveableRect() override;
};