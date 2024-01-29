#pragma once
#include <Windows.h>
#include "framework.h"

enum WindowXY
{
	MAIN_X = 380,
	MAIN_Y = 60,
	MAIN_W = 497,
	MAIN_H = 520,

	SUB_X = 250,
	SUB_Y = 110,
	SUB_W = 20,
	SUB_H = 100,

	SUB_PROMOTION_X = SUB_X,
	SUB_PROMOTION_Y = SUB_Y * 2,
	SUB_PROMOTION_W = SUB_W,
	SUB_PROMOTION_H = SUB_H * 2,
	
	/*	SUB_X = 700,
	SUB_Y = 5,
	SUB_W = 400,
	SUB_H = 400,*/
};


class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	SIZE m_Size;


public:
	BitMap();
	~BitMap();

	void Init(HDC hdc, char* FileName);
	void Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize); //�� ���(���� ����)
	void DrawBG(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize); //��� ���(�����״��)
	void DrawSubWin(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize); //Sub Win ���(���� 2�� �÷���)
	void DrawTransparent(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize); //�����ϰ� ���(����)
	//void DrawMove(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	//void DrawBackGroundIMG(HDC hdc);
	inline SIZE GetSize() { return m_Size; }
};

