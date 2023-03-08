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
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//���� �̵�
	Set_Rect(map, 0, move_iY, QUEEN_LINE_COUNT);
	//�Ĺ� �̵�
	Set_Rect(map, 0, -move_iY, QUEEN_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, -1, 0, QUEEN_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, 1, 0, QUEEN_LINE_COUNT);

	//--------------------------------------------

	//1.���� �̵�
	Set_Rect(map, 1, 1, QUEEN_LINE_COUNT);
	//2.���� �̵�
	Set_Rect(map, 1, -1, QUEEN_LINE_COUNT);
	//3.���� �̵�
	Set_Rect(map, -1, 1, QUEEN_LINE_COUNT);
	//4.���� �̵�
	Set_Rect(map, -1, -1, QUEEN_LINE_COUNT);
}