#include "BitMapManager.h"

//BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMG_COUNT + IMG_BG_COUNT + 1];
}


void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	HDC hdc = GetDC(hWnd);
	int i; //m_parrBitMap에 저장하기위해

	//흑말
	for (i = 0; i < IMG_BLACK_COUNT; i++) //TODO::0~6으로 변경
	{
		sprintf_s(buf, "RES//block_b_%d.bmp", i);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//백말
	for (int j = 0; j < IMG_WHITE_COUNT; j++)
	{
		sprintf_s(buf, "RES//block_w_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}
	
	//배경 12~13
	for (int j = 0; j < IMG_BG_COUNT; j++)
	{
		sprintf_s(buf, "RES//tile_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}
	
	//투명화 이미지 14
	sprintf_s(buf, "RES//MoveableTileMask.bmp", i);
	m_parrBitMap[i].Init(hdc, buf);

	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}