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
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//1.���� �̵�
	Set_Rect(map, 1, 1, BISHOP_LINE_COUNT);
	//2.���� �̵�
	Set_Rect(map, 1, -1, BISHOP_LINE_COUNT);
	//3.���� �̵�
	Set_Rect(map, -1, 1, BISHOP_LINE_COUNT);
	//4.���� �̵�
	Set_Rect(map, -1, -1, BISHOP_LINE_COUNT);
}