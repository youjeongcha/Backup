#include "Pawn.h"
#include "GameManager.h"

#define GMMgr GameManager::Get_Instance()

Pawn::Pawn() 
{
	
}

Pawn::Pawn(BitMapManager& BitMapMgr_Main, const CAMP _campColor, const IMG _Index, const int _X, const int _Y) : Piece(BitMapMgr_Main, _campColor, _Index, _X, _Y)
{
	firstMoveCheck = true;
}

Pawn::~Pawn()
{
}

//bool Pawn::ColliderCheck_Piece(POINT point)
//{
//	if (PtInRect(&m_BitMapRect, point))
//	{
//		//TODO::�ش� �⹰�� �̵� ���� üũ ��. ���θ��� �� ������ �̵�.
//		m_moveCheck = true; //�̵� ǥ�� üũ ��û�� ���Դ���
//		return true;
//	}
//	return false;
//}
//
//bool Pawn::ColliderCheck_CanMove(POINT point)
//{
//	m_moveCheck = false; //
//
//	for (auto rect : m_BitMapRect_MoveList)
//	{
//		if (PtInRect(&rect, point))
//		{
//			//�̵��� �� �ִ� ĭ�� ���� ���
//			Move(rect);
//			firstMoveCheck = false; //ù��° �̵����� false�� �����Ǿ�� �Ѵ�.
//			return true;
//		}
//	}
//
//	//���� �̵��� �Ͼ�� �ʰ� �̵� ���� ĭ üũ�� �������� list�� �ʱ�ȭ �Ǿ�� �Ѵ�.
//	//(�ʱ�ȭ ���� ������ i�� �þ�� ǥ�ð� ���������� ��� �þ��.)
//	m_BitMapRect_MoveList.clear();
//	return false;
//}

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
	for (int i = 0; i < PAWN::MAX_MOVE_COUNT; i++)
	{
		RECT TmpRect;
		
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

		if ((eatableCheck != CAMP_NONE) &&
			(eatableCheck != m_CampColor))
		{
			TmpRect.top = (m_iY + move_iY) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);
		}
	}
}