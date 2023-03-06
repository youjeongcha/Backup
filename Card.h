#pragma once
#include"BitMap.h"
#include"BitMapManager.h"
enum CARD
{
	CARD_FRONT,
	CARD_REAR,
	CARD_END
};

enum CARD_SIZE
{
	CARD_SIZE_W = 100,
	CARD_SIZE_H = 80,
};


class Card
{
private:
	CARD m_eCardState;
	BitMap* m_pBitMap[CARD_END];
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
	//ī�� �ո� + �޸� ��Ÿ�� active ����. �ƿ� ȭ�鿡 ������ Set_Inactive()�� false
	bool m_activeCheck;
	IMAGE m_saveIMG;
public:
	Card();
	Card(const Card& earseCard);
	~Card();

	void Init(BitMapManager* BitMapMgr_Main, IMAGE Index, int x, int y);
	void Set_Front_IMG(BitMapManager* BitMapMgr_Main, IMAGE Index);
	void Draw(HDC hdc);
	//Ŭ���� ī�� �� > ��
	bool ColliderCheck(POINT point);
	bool Check_CardState_Front();

	CARD Get_CardState() { return m_eCardState; }

	void Set_CardState(CARD _eCardState) { m_eCardState = _eCardState; } //ī�� ��ȯ
	void Set_RandXY(int _x, int _y);
	void Set_Inactive() { m_activeCheck = false; }
	bool IsActive()const { return m_activeCheck; }
};