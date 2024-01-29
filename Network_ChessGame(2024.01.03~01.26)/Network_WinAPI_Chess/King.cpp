#include "King.h"
#include "GameManager.h"


King::King(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
}

King::~King()
{
}


void King::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//전방 이동
	Set_Rect(map, 0, move_iY, KING_LINE_COUNT);
	//후방 이동
	Set_Rect(map, 0, -move_iY, KING_LINE_COUNT);
	//좌측 이동
	Set_Rect(map, -1, 0, KING_LINE_COUNT);
	//우측 이동
	Set_Rect(map, 1, 0, KING_LINE_COUNT);

	//------------------------------------------

	//1.동남 이동
	Set_Rect(map, 1, 1, KING_LINE_COUNT);
	//2.동북 이동
	Set_Rect(map, 1, -1, KING_LINE_COUNT);
	//3.서남 이동
	Set_Rect(map, -1, 1, KING_LINE_COUNT);
	//4.서북 이동
	Set_Rect(map, -1, -1, KING_LINE_COUNT);
}
