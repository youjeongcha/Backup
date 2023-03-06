#include "Card.h"



Card::Card()
{//TODO::�޸����� ���� ����
	m_eCardState = CARD_FRONT;
	m_activeCheck = true;
}

Card::Card(const Card& earseCard)
{
	m_eCardState = earseCard.m_eCardState;
	m_pBitMap[CARD_END] = *earseCard.m_pBitMap;
	m_ix = earseCard.m_ix;
	m_iy = earseCard.m_iy;
	m_BitMapRect = earseCard.m_BitMapRect;
}

void Card::Set_RandXY(int _x, int _y)
{
	m_ix = _x;
	m_iy = _y;

	//�� m_BitMapRect�� ������� Ŀ�����ؼ�. _x�� _y�� ������ �� ���õǰ�. �׸��� m_BitMapRect�� �����ؼ� ����Ҽ� �ֵ��� �ϴ� ��
	m_BitMapRect.left = _x; //x�� ���� //TODO::���� ������ ���濡 ���� �簢 ������ �ٲ��� �Ѵ�.
	m_BitMapRect.top = _y; //y�� ����
	m_BitMapRect.right = m_BitMapRect.left + CARD_SIZE_W;
	m_BitMapRect.bottom = m_BitMapRect.top + CARD_SIZE_H;
}

void Card::Init(BitMapManager* BitMapMgr_Main, IMAGE Index, int x, int y)
{
	m_saveIMG = Index;
	m_pBitMap[CARD_FRONT] = BitMapMgr_Main->GetImage(Index);
	m_pBitMap[CARD_REAR] = BitMapMgr_Main->GetImage(IMAGE_BLACK);
	Set_RandXY(x, y);
}
 
void Card::Set_Front_IMG(BitMapManager* BitMapMgr_Main, IMAGE Index)
{
	m_pBitMap[CARD_FRONT] = BitMapMgr_Main->GetImage(IMAGE(Index + IMAGE_CHANGE_INDEX));//bitMap �ҷ����� 20~24�� �ϰ�. ȣ���� 6~10���� ��
}

void Card::Draw(HDC hdc)
{
	if (m_activeCheck)
		m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy, CARD_SIZE_W, CARD_SIZE_H); //TODO::W H ���� enum���� 
	//Rectangle(hdc, m_BitMapRect.left, m_BitMapRect.top , m_BitMapRect.right, m_BitMapRect.bottom);
}

bool Card::ColliderCheck(POINT point)
{//�޸��� �ո����� �ٲ�� �͸� �ش��Լ��� �ΰ�. TODO::�ո��� �޸����� ���ư��� �Լ��� ���� ������ �Ѵ�.
	if (PtInRect(&m_BitMapRect, point) && m_eCardState != CARD_FRONT)
	{
		m_eCardState = CARD_FRONT;
		return true; //�ո��� ���¿����� �޸����� ������ ���� �����ϱ�. �ո��϶��� false�� �����ؼ� ȭ�� �� ����� �ٽ� ��� ���ϰԲ�
	}
	return false;
}

bool Card::Check_CardState_Front()
{
	if (m_eCardState == CARD_FRONT) 
		return true;

	return false;
}

Card::~Card()
{
}
