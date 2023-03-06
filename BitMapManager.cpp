#include "BitMapManager.h"

//BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMAGE_COUNT * 2 + IMG_BG_COUNT + 1];
}


void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	HDC hdc = GetDC(hWnd);
	int i;

	//기본 카드 이미지 0~4
	for (i = IMAGE_START; i <= IMAGE_COUNT; i++)
	{
		sprintf_s(buf, "RES//0%d.bmp", i);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//변할 카드 이미지 4~9
	for (int j = IMAGE_CHANGE_START; j < IMAGE_CHANGE_RANGE; j++)
	{
		sprintf_s(buf, "RES//%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	//메인 배경 + 서브 배경 11~16
	for (int j = IMG_BG_START; j <= SUB_IMG_BG_END; j++)
	{
		sprintf_s(buf, "RES//%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}
	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}
