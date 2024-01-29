#include "Piece.h"
#include "GameManager.h"
//#include "PiecesManager.h"
//
//#define GMMgr GameManager::Get_Instance()
//#define PiecesMgr PiecesManager::Get_Instance()
//��GameManager.h���� �����صΰ� ����Ѵ�. cpp���� �ߺ� ������ �ʿ� ����


Piece::Piece(Piece* piece)
//Piece::Piece(Piece* piece)
{
	m_moveCheck = false;

	//m_pBitMap = piece.m_pBitMap;
	//m_pBitMap_Move = piece.m_pBitMap_Move; //�̵� ǥ��
	//m_moveCheck = piece.m_moveCheck; //�̵� ǥ�� üũ ��û�� ���Դ���
	//m_BitMapRect = piece.m_BitMapRect;
	////m_moveRect; //�̵� ��ų rect �ӽ� �����
	//m_BitMapRect_MoveList = piece.m_BitMapRect_MoveList;
	//m_iX = piece.m_iX; //map������ �ε���
	//m_iY = piece.m_iY;
	//move_iY = piece.move_iY; //BW �� �̵� ���� ����
	//m_Piece = piece.m_Piece; //�ش� �⹰�� enum;
	//m_CampColor = piece.m_CampColor; //�ش� �⹰�� ����

	//m_pBitMap = piece.m_pBitMap;
	m_pBitMap_Move = piece->m_pBitMap_Move; //�̵� ǥ��
	m_moveCheck = piece->m_moveCheck; //�̵� ǥ�� üũ ��û�� ���Դ���
	m_BitMapRect = piece->m_BitMapRect;
	//m_moveRect; //�̵� ��ų rect �ӽ� �����
	m_BitMapRect_MoveList = piece->m_BitMapRect_MoveList;
	m_iX = piece->m_iX; //map������ �ε���
	m_iY = piece->m_iY;
	move_iY = piece->move_iY; //BW �� �̵� ���� ����
	m_Piece = piece->m_Piece; //�ش� �⹰�� enum;
	m_CampColor = piece->m_CampColor; //�ش� �⹰�� ����
}

Piece::Piece(BitMapManager& BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y)
{
	m_moveCheck = false;

    m_CampColor = _campColor;
    m_Piece = _Index;
    m_pBitMap = BitMapMgr_Main.GetImage(_Index);
    m_pBitMap_Move = BitMapMgr_Main.GetImage(IMG_MOVE);
    
    this->m_iX = _X;
    this->m_iY = _Y;

	switch (m_CampColor)
	{
	case CAMP_WHITE:
		move_iY = -1;
		break;
	case CAMP_BLACK:
		move_iY = 1;
		break;
	default:
		break;
	}

    m_BitMapRect.left = _X * IMG_BG_SIZE;
    m_BitMapRect.top = _Y * IMG_BG_SIZE;
    m_BitMapRect.right = m_BitMapRect.left + IMG_BG_SIZE;
    m_BitMapRect.bottom = m_BitMapRect.top + IMG_BG_SIZE;
}

Piece::~Piece()
{
}


bool Piece::ColliderCheck_Piece(POINT point)
{
	//����, �� ���� Ŭ���ߴ��� and �ش� ���� ������ ���� �´���(�ش� �������� �� ���� ����)
	//���� Ȯ���� get���� PieceMgr���� �ݺ��� ������ ���� Ȯ��
	if (PtInRect(&m_BitMapRect, point))//) &&(GMMgr->Get_PlayerTurn() == m_CampColor))
	{
		//�ش� �⹰�� �̵� ���� üũ ��. ���θ��� �� ������ �̵�.
		m_moveCheck = true; //�̵� ǥ�� üũ ��û�� ���Դ���
		return true;
	}
	return false;
}

bool Piece::ColliderCheck_Moveable(POINT point)
{
	m_moveCheck = false;

	for (auto rect : m_BitMapRect_MoveList)
	{
		if (PtInRect(&rect, point))
		{
			//��ǥ �̵� : �̵��� �� �ִ� ĭ�� ���� ���
			m_moveRect = rect;
			firstMoveCheck = false; //ù��° �̵����� false�� �����Ǿ�� �Ѵ�.

			////������ move ���¸� �ľ�
			//if (m_MoveState == CAN_FIRSTMOVE)
			//{
			//	//(ĳ���� �̱���)King�� ĳ������ ���� CAN_FIRSTMOVE > CASTLING > NONE�� ���·� ��ȯ
			//	//Pawn�� ó�� �̵��ϴ� ��� 
			//	if (m_Piece == IMG_BLACK_PAWN || m_Piece == IMG_WHITE_PAWN)
			//	{

			//	}
			//}
			return true;
		}
	}

	//���� �̵��� �Ͼ�� �ʰ� �̵� ���� ĭ üũ�� �������� list�� �ʱ�ȭ �Ǿ�� �Ѵ�.
	//(�ʱ�ȭ ���� ������ i�� �þ�� ǥ�ð� ���������� ��� �þ��.)
	m_BitMapRect_MoveList.clear();
	return false;
}

//��peice SetMoveableRect�� �����Լ��� ����Ѵ�.
//void Piece::SetMoveableRect()
//{
//
//}

void Piece::DrawMoveable(HDC hdc)
{	//m_BitMapRect_MoveList�� �̸� �־�� �̹��� ����ϱ�
	//PRINT_XY_PLUS �߾ӿ� ��� ����
	for (auto rect : m_BitMapRect_MoveList)
		m_pBitMap_Move->Draw(hdc, rect.left + PRINT_XY_PLUS, rect.top + PRINT_XY_PLUS, IMG_SIZE, IMG_SIZE);
}


void Piece::Move()
{
	//���� ĭ ����
	GMMgr->Set_Map(CAMP_NONE, m_iX, m_iY);

	//m_moveRect�� �̵��ؾ� �� ��ġ�� ������ �ְ�
	//m_iX, m_iY���� map���� ����� �ε���
    m_iX = m_moveRect.left / IMG_BG_SIZE;
    m_iY = m_moveRect.top / IMG_BG_SIZE;

	m_BitMapRect = m_moveRect;

	//�̵��� ĭ �⹰ ������ �����Ѵ� ����
    //XY��ǥ ID ������ GM�� CAMP�� Map�� ���� map��Ȳ�� �������ش�.
    GMMgr->Set_Map(m_CampColor, m_iX, m_iY);
    m_BitMapRect_MoveList.clear();
}

void Piece::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_iX * IMG_BG_SIZE + PRINT_XY_PLUS, m_iY * IMG_BG_SIZE + PRINT_XY_PLUS, IMG_SIZE, IMG_SIZE);
}


void Piece::Set_Rect(CAMP map[][BOARD_Y], int move_iX, int move_iY, int count)
{
	CAMP moveableCheck;
	bool eatableCheck;

	for (int i = 1; i <= count; i++)
	{
		moveableCheck = map[m_iX + move_iX * i][m_iY + move_iY * i];
		eatableCheck = (moveableCheck != CAMP_NONE) && (moveableCheck != m_CampColor);

		if ((moveableCheck == CAMP_NONE) || (eatableCheck))
		{
			RECT TmpRect;
			TmpRect.left = (m_iX + move_iX * i) * IMG_BG_SIZE;
			TmpRect.top = (m_iY + move_iY * i) * IMG_BG_SIZE;
			TmpRect.right = TmpRect.left + IMG_BG_SIZE;
			TmpRect.bottom = TmpRect.top + IMG_BG_SIZE;
			m_BitMapRect_MoveList.push_back(TmpRect);

			if (eatableCheck)
				break;
		}
		else
			break;
	}
}


//ü�� ��Ʈ��ũ �߰� �ڵ�


void Piece::MovePieceData()
{
	//�� �����̱� �� map�� �ε����� �����ص־�. �ٸ� �÷��̾ �̵��� ���� �Ǻ��� �� �ִ�.
	GMMgr->Set_moveData(m_iX, m_iY, m_moveRect);
}