#pragma once
#include"BitMap.h"
#include<stdio.h>
//#include<vector>
//0~4 오리지널 이미지, 20~24 ReInit 이미지. but 같은 동물 사진끼리 m_parrBitMap에 저장되는 인덱스는 같아야 한다.

enum IMAGE
{
	IMAGE_START,
	IMAGE_TIGER = 0,
	IMAGE_FOX,
	IMAGE_HORSE,
	IMAGE_LIZARD,
	IMAGE_SQUIRREL,
	//IMAGE_HORSE,
	//IMAGE_CAT,
	//IMAGE_MONKEY,
	//IMAGE_FROG,
	//IMAGE_CHICKEN,
	IMAGE_BLACK,
	IMAGE_COUNT = IMAGE_SQUIRREL + 1,

	//색 출력 망한 이미지
	IMAGE_CHANGE_START= 20,
	IMAGE_CHANGE_TIGER = 20,
	IMAGE_CHANGE_FOX,
	IMAGE_CHANGE_HORSE,
	IMAGE_CHANGE_LIZARD,
	IMAGE_CHANGE_SQUIRREL,
	IMAGE_CHANGE_COUNT = IMAGE_CHANGE_SQUIRREL - IMAGE_CHANGE_START + 1,
	IMAGE_CHANGE_RANGE = IMAGE_CHANGE_TIGER + IMAGE_CHANGE_COUNT,
	IMAGE_CHANGE_INDEX = 6,
};

enum IMG_BG
{
	IMG_BG_START = 11,
	IMG_BG_MAIN = 11,
	IMG_BG_STORY,
	IMG_BG_RABBIT,
	IMG_BG_CARDGAME,
	IMG_BG_GAMEOVER,
	IMG_BG_GAMECLEAR,

	SUB_IMG_BG_FIRST = 17,
	SUB_IMG_BG_END,

	IMG_BG_COUNT = SUB_IMG_BG_END - IMG_BG_MAIN + 1, //배경 이미지 갯수
};


//싱글톤
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap은 하나만 있어도 되기때문에 객체를 생성하지 않고 *로 사용한다. 배열 사용.
	//static BitMapManager* m_hThis;
public:
	//static BitMapManager* GetInstance()
	//{
	//	if (m_hThis == NULL)
	//		m_hThis = new BitMapManager;
	//	return m_hThis;
	//}
	BitMapManager();
	~BitMapManager();

	//Card.cpp에서 사용하고 있다.
	BitMap* GetImage(IMAGE index) { return &m_parrBitMap[index]; }
	//GameManager.cpp에서 사용
	BitMap* GetBGImage(IMG_BG index) { return &m_parrBitMap[index]; }

	void Init(HWND hWnd);
};

