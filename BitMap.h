#pragma once
#include <Windows.h>

enum WindowXY
{
	MAIN_X = 380,
	MAIN_Y = 60,
	MAIN_W = 497,
	MAIN_H = 520,

	SUB_X = 700,
	SUB_Y = 5,
	SUB_W = 400,
	SUB_H = 400,
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
	void Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	void DrawBG(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	//void DrawMoveable(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	void DrawMove(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	//void DrawBackGroundIMG(HDC hdc);
	inline SIZE GetSize() { return m_Size; }
};

