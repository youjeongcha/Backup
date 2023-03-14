#include "Bishop.h"
#include "GameManager.h"


Bishop::Bishop(Piece _piece, IMG _Index) : Piece(_piece)
{
	m_Piece = _Index;
	m_pBitMap = BitMapMgr->GetImage(_Index);
}

Bishop::Bishop(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
}

Bishop::~Bishop()
{
}


void Bishop::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//1.동남 이동
	Set_Rect(map, 1, 1, BISHOP_LINE_COUNT);
	//2.동북 이동
	Set_Rect(map, 1, -1, BISHOP_LINE_COUNT);
	//3.서남 이동
	Set_Rect(map, -1, 1, BISHOP_LINE_COUNT);
	//4.서북 이동
	Set_Rect(map, -1, -1, BISHOP_LINE_COUNT);
}