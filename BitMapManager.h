#pragma once
#include"BitMap.h"
#include<stdio.h>
//0~4 �������� �̹���, 20~24 ReInit �̹���. but ���� ���� �������� m_parrBitMap�� ����Ǵ� �ε����� ���ƾ� �Ѵ�.

enum IMG
{	
	IMG_BLACK_START,
	IMG_BLACK_PAWN = IMG_BLACK_START,
	IMG_BLACK_ROOK,
	IMG_BLACK_KNIGHT,
	IMG_BLACK_BISHOP,
	IMG_BLACK_QUEEN,
	IMG_BLACK_KING,
	IMG_BLACK_COUNT = 6,


	IMG_WHITE_START = 6,
	IMG_WHITE_PAWN = IMG_WHITE_START,
	IMG_WHITE_ROOK,
	IMG_WHITE_KNIGHT,
	IMG_WHITE_BISHOP,
	IMG_WHITE_QUEEN,
	IMG_WHITE_KING,
	IMG_WHITE_COUNT = 6,


	IMG_COUNT = IMG_WHITE_COUNT + IMG_BLACK_COUNT,

	//���
	IMG_BG_WHITE = 12,
	IMG_BG_BLACK,

	IMG_BG_COUNT = 2,

	//�̵� ���� �̹���
	IMG_MOVE = 14,


	//----------------------���-----------------------------
	PRINT_WH_MINUS = 18, //20, //�ʺ� ���� ����(�̹��� ũ�� ����)
	PRINT_XY_PLUS = PRINT_WH_MINUS / 2, //�̹��� ��� ��ǥ ����

	//�̹��� ������
	IMG_BG_SIZE = 60,
	IMG_SIZE = IMG_BG_SIZE - PRINT_WH_MINUS,
};

//enum IMG_BG
//{
//	IMG_BG_WHITE,
//	IMG_BG_BLACK,
//
//	IMG_BG_COUNT,
//};


//�̱���
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap�� �ϳ��� �־ �Ǳ⶧���� ��ü�� �������� �ʰ� *�� ����Ѵ�. �迭 ���.
	static BitMapManager* m_hThis;
public:
	static BitMapManager* GetInstance()
	{
		if (NULL == m_hThis)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	BitMapManager();
	~BitMapManager();

	BitMap* GetImage(IMG index) { return &m_parrBitMap[index]; }

	void Init(HWND hWnd);
};