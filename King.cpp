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
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//���� �̵�
	Set_Rect(map, 0, move_iY, KING_LINE_COUNT);
	//�Ĺ� �̵�
	Set_Rect(map, 0, -move_iY, KING_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, -1, 0, KING_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, 1, 0, KING_LINE_COUNT);

	//------------------------------------------

	//1.���� �̵�
	Set_Rect(map, 1, 1, KING_LINE_COUNT);
	//2.���� �̵�
	Set_Rect(map, 1, -1, KING_LINE_COUNT);
	//3.���� �̵�
	Set_Rect(map, -1, 1, KING_LINE_COUNT);
	//4.���� �̵�
	Set_Rect(map, -1, -1, KING_LINE_COUNT);
}
