#pragma once
#include<Windows.h>

enum WindowXY
{
	MAIN_X = 200,
	MAIN_Y = 0,
	MAIN_W = 800,
	MAIN_H = 600,

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
	//HBITMAP OldBitmap; //���� �ľ�� �����̾�����. ���� �̹������� ������ ���� ������ �־ ����� �ʿ�X
	SIZE m_Size;
public:
	void Init(HDC hdc, char* FileName);
	void Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize);
	void DrawBackGroundIMG(HDC hdc); //���� :: ��� ����?
	inline SIZE GetSize()
	{
		return m_Size;
	}
	BitMap();
	~BitMap();
};

