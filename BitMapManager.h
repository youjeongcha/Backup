#pragma once
#include"BitMap.h"
#include<stdio.h>
//0~4 오리지널 이미지, 20~24 ReInit 이미지. but 같은 동물 사진끼리 m_parrBitMap에 저장되는 인덱스는 같아야 한다.

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

	//배경
	IMG_BG_WHITE = 12,
	IMG_BG_BLACK,

	IMG_BG_COUNT = 2,

	//이동 가능 이미지
	IMG_MOVE = 14,


	//----------------------출력-----------------------------
	PRINT_WH_MINUS = 18, //20, //너비 높이 감소(이미지 크기 조절)
	PRINT_XY_PLUS = PRINT_WH_MINUS / 2, //이미지 출력 좌표 조절

	//이미지 사이즈
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


//싱글톤
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap은 하나만 있어도 되기때문에 객체를 생성하지 않고 *로 사용한다. 배열 사용.
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