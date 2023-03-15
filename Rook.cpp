#include "Rook.h"
#include "GameManager.h"


Rook::Rook(Piece* _piece, IMG _Index) : Piece(*_piece)
{
	m_Piece = _Index;
	m_pBitMap = BitMapMgr->GetImage(_Index);
}

Rook::Rook(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
}

Rook::~Rook()
{
}


void Rook::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP(*map)[BOARD_Y] = GMMgr->Get_Map();

	//���� �̵�
	Set_Rect(map, 0, move_iY, ROOK_LINE_COUNT);
	//�Ĺ� �̵�
	Set_Rect(map, 0, -move_iY, ROOK_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, -1, 0, ROOK_LINE_COUNT);
	//���� �̵�
	Set_Rect(map, 1, 0, ROOK_LINE_COUNT);
}