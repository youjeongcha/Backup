#pragma once
#pragma comment(lib, "msimg32.lib")

#include<Windows.h>
#include "framework.h"


class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	SIZE m_Size;

public:
	void Init(HDC hdc, char* FileName);
	void Draw(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize);
	void DrawTransparent(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize); //�����ϰ� ���(����)
	inline SIZE GetSize() { return m_Size; }
	BitMap();
	~BitMap();
};