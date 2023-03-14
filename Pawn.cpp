#include "Pawn.h"
#include "GameManager.h"


Pawn::Pawn(Piece _piece, IMG _Index) : Piece(_piece)
{
	//������ ���ؼ� �� ��� �̴ϼȶ������� ������� �ʴ´�.
	/*m_Piece = _Index;
	m_pBitMap = GMMgr->Get_BitMapMain()->GetImage(_Index);*/
}

Pawn::Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
	firstMoveCheck = true;
}

Pawn::~Pawn()
{
}


void Pawn::SetMoveableRect()
{
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP (*map)[BOARD_Y] = GMMgr->Get_Map();
	CAMP eatableCheck;
	int move_iX = 1;

	//���� �̵�
	for (int i = 1; i <= PAWN::MAX_MOVE_COUNT; i++)
	{
		//������ ��ĭ(��ĭ)
		if (map[m_iX][m_iY + move_iY * i] == CAMP_NONE) //������ ���� ������ ������
		{ //�̵� ������ ���� Ž�� > m_BitMapRect_MoveList�� rect push
			RECT TmpRect;
			TmpRect.left = m_iX * IMG_BG_SIZE;
			TmpRect.top = (m_iY + move_iY * i) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
		else
			break;

		//ù��° �̵�(�ΰ� �̵� ���� ��)�� �̹� �� ���
		if (firstMoveCheck == false)
			break;
	}


	//���� �밢���� �� �⹰ ������! �Ա����� rect����(����, ����)
	//+���Ļ� ���
	for (int i = 0; i < PAWN::MAX_MOVE_COUNT; i++)
	{
		RECT TmpRect;
		
		//���� �⹰�� Ư�� ��ǥ�� �ִ��� Ȯ���� �ϱ� ���� ����
		//left���� Ư�����̱⿡ ���� ������ ���ش�.
		switch (i)
		{
		case PAWN::EAT_LEFT:
			eatableCheck = map[m_iX - move_iX][m_iY + move_iY];
			TmpRect.left = (m_iX - move_iX) * IMG_BG_SIZE;
			break;
		case PAWN::EAT_RIGHT:
			eatableCheck = map[m_iX + move_iX][m_iY + move_iY];
			TmpRect.left = (m_iX + move_iX) * IMG_BG_SIZE;
			break;
		}

		//�ش� �⹰�� �԰� �����ϰԵ� �ڸ���(rect) �����Ѵ�.

		//�밢�� �տ� ������ �⹰�� �ִ� ��� + ���Ļ�(�� �⹰�� �Դ� ����)
		if ((eatableCheck != CAMP_NONE) &&
			(eatableCheck != m_CampColor))
		{
			TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
	}

	////��+���Ļ� ���//������ ���ؼ� ���� ����� �ؼ� ���� ������(�̵�)�� ����
	//for (int i = ENPASSANT_LEFT; i <= PAWN::ENPASSANT_RIGHT; i++)
	//{
	//	RECT TmpRect;

	//	//���� �⹰�� Ư�� ��ǥ�� �ִ��� Ȯ���� �ϱ� ���� ����
	//	//left���� Ư�����̱⿡ ���� ������ ���ش�.
	//	switch (i)
	//	{
	//	case PAWN::ENPASSANT_LEFT:
	//		eatableCheck = map[m_iX - move_iX][m_iY];
	//		TmpRect.left = (m_iX - move_iX) * IMG_BG_SIZE;
	//		break;
	//	case PAWN::ENPASSANT_RIGHT:
	//		eatableCheck = map[m_iX + move_iX][m_iY];
	//		TmpRect.left = (m_iX + move_iX) * IMG_BG_SIZE;
	//		break;
	//	}

	//	//�ش� �⹰�� �԰� �����ϰԵ� �ڸ���(rect) �����Ѵ�.

	//	//left�� right�� ���� �Ͽ� 2ĭ �̵��� ������ �⹰�� �ִ� ��� + ���Ļ�(�� �⹰�� �Դ� ����)
	//	if ((eatableCheck != CAMP_NONE) &&
	//		(eatableCheck != m_CampColor))
	//	{
	//		TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
	//		TmpRect.right = TmpRect.left + IMG_BG_SIZE;
	//		TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
	//		m_BitMapRect_MoveList.push_back(TmpRect);
	//	}
	//}
}