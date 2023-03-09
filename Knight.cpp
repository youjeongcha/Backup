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
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//���� ��*2 ��*1 �� ���ڰ� 2ĭ �̵�
	//1.���� �̵�
	Set_Rect(map, 2, 1, KNIGHT_LINE_COUNT);
	//2.���� �̵�
	Set_Rect(map, 2, -1, KNIGHT_LINE_COUNT);
	//3.���� �̵�
	Set_Rect(map, -2, 1, KNIGHT_LINE_COUNT);
	//4.���� �̵�
	Set_Rect(map, -2, -1, KNIGHT_LINE_COUNT);

	//------------------------------------------
	
	//5.�ϵ� �̵�
	Set_Rect(map, 1, -2, KNIGHT_LINE_COUNT);
	//6.�ϼ� �̵�
	Set_Rect(map, -1, -2, KNIGHT_LINE_COUNT);
	//7.���� �̵�
	Set_Rect(map, 1, 2, KNIGHT_LINE_COUNT);
	//8.���� �̵�
	Set_Rect(map, -1, 2, KNIGHT_LINE_COUNT);
}