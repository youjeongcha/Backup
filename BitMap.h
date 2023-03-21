#pragma once
#pragma comment(lib, "msimg32.lib")

#include<Windows.h>
#include "framework.h"

enum WindowXY
{
	MAIN_X = 200,
	MAIN_Y = 100,
	MAIN_W = 900,
	MAIN_H = 450,
};
class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	SIZE m_Size;

public:
	void Init(HDC hdc, char* FileName);
	void Draw(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize);
	void DrawTransparent(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize); //투명하게 출력(투명도)
	inline SIZE GetSize() { return m_Size; }
	BitMap();
	~BitMap();
};