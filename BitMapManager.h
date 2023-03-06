#pragma once
#include"BitMap.h"
#include<stdio.h>
//#include<vector>
//0~4 �������� �̹���, 20~24 ReInit �̹���. but ���� ���� �������� m_parrBitMap�� ����Ǵ� �ε����� ���ƾ� �Ѵ�.

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

	//�� ��� ���� �̹���
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

	IMG_BG_COUNT = SUB_IMG_BG_END - IMG_BG_MAIN + 1, //��� �̹��� ����
};


//�̱���
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap�� �ϳ��� �־ �Ǳ⶧���� ��ü�� �������� �ʰ� *�� ����Ѵ�. �迭 ���.
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

	//Card.cpp���� ����ϰ� �ִ�.
	BitMap* GetImage(IMAGE index) { return &m_parrBitMap[index]; }
	//GameManager.cpp���� ���
	BitMap* GetBGImage(IMG_BG index) { return &m_parrBitMap[index]; }

	void Init(HWND hWnd);
};

