#include "Queen.h"
#include "GameManager.h"

#define GMMgr GameManager::Get_Instance()

Queen::Queen()
{
}

Queen::Queen(Piece _piece, IMG _Index) : Piece(_piece)
{
	m_Piece = _Index;
	m_pBitMap = GMMgr->Get_BitMapMain()->GetImage(_Index);
}

Queen::Queen(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
}

Queen::~Queen()
{
}

//bool Queen::ColliderCheck_Piece(POINT point)
//{
//	return false;
//}
//
//bool Queen::ColliderCheck_CanMove(POINT point)
//{
//	return false;
//}


void Queen::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//전방 이동
	Set_Rect(map, 0, move_iY, QUEEN_LINE_COUNT);
	//후방 이동
	Set_Rect(map, 0, -move_iY, QUEEN_LINE_COUNT);
	//좌측 이동
	Set_Rect(map, -1, 0, QUEEN_LINE_COUNT);
	//우측 이동
	Set_Rect(map, 1, 0, QUEEN_LINE_COUNT);

	//--------------------------------------------

	//1.동남 이동
	Set_Rect(map, 1, 1, QUEEN_LINE_COUNT);
	//2.동북 이동
	Set_Rect(map, 1, -1, QUEEN_LINE_COUNT);
	//3.서남 이동
	Set_Rect(map, -1, 1, QUEEN_LINE_COUNT);
	//4.서북 이동
	Set_Rect(map, -1, -1, QUEEN_LINE_COUNT);
}