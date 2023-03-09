#include "Knight.h"
#include "GameManager.h"

#define GMMgr GameManager::Get_Instance()


Knight::Knight(Piece _piece, IMG _Index) : Piece(_piece)
{
	m_Piece = _Index;
	m_pBitMap = GMMgr->Get_BitMapMain()->GetImage(_Index);
}

Knight::Knight(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
}

Knight::~Knight()
{
}


void Knight::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//동남 동*2 남*1 앞 글자가 2칸 이동
	//1.동남 이동
	Set_Rect(map, 2, 1, KNIGHT_LINE_COUNT);
	//2.동북 이동
	Set_Rect(map, 2, -1, KNIGHT_LINE_COUNT);
	//3.서남 이동
	Set_Rect(map, -2, 1, KNIGHT_LINE_COUNT);
	//4.서북 이동
	Set_Rect(map, -2, -1, KNIGHT_LINE_COUNT);

	//------------------------------------------
	
	//5.북동 이동
	Set_Rect(map, 1, -2, KNIGHT_LINE_COUNT);
	//6.북서 이동
	Set_Rect(map, -1, -2, KNIGHT_LINE_COUNT);
	//7.남동 이동
	Set_Rect(map, 1, 2, KNIGHT_LINE_COUNT);
	//8.남서 이동
	Set_Rect(map, -1, 2, KNIGHT_LINE_COUNT);
}