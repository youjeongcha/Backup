#include "Card.h"



Card::Card()
{//TODO::뒷면으로 게임 시작
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

	//★ m_BitMapRect를 상속으로 커스텀해서. _x와 _y를 넣으면 다 세팅되게. 그리고 m_BitMapRect로 접근해서 사용할수 있도록 하는 거
	m_BitMapRect.left = _x; //x랑 같다 //TODO::사진 사이즈 변경에 따라 사각 영역도 바뀌어야 한다.
	m_BitMapRect.top = _y; //y랑 같다
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
	m_pBitMap[CARD_FRONT] = BitMapMgr_Main->GetImage(IMAGE(Index + IMAGE_CHANGE_INDEX));//bitMap 불러오기 20~24로 하고. 호출은 6~10으로 함
}

void Card::Draw(HDC hdc)
{
	if (m_activeCheck)
		m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy, CARD_SIZE_W, CARD_SIZE_H); //TODO::W H 설정 enum으로 
	//Rectangle(hdc, m_BitMapRect.left, m_BitMapRect.top , m_BitMapRect.right, m_BitMapRect.bottom);
}

bool Card::ColliderCheck(POINT point)
{//뒷면이 앞면으로 바뀌는 것만 해당함수에 두고. TODO::앞면이 뒷면으로 돌아가는 함수는 따로 만들어야 한다.
	if (PtInRect(&m_BitMapRect, point) && m_eCardState != CARD_FRONT)
	{
		m_eCardState = CARD_FRONT;
		return true; //앞면인 상태에서는 뒷면으로 뒤집을 일이 없으니까. 앞면일때는 false를 리턴해서 화면 다 지우고 다시 출력 안하게끔
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
