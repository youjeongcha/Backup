#pragma once
#include "EngineMecro.h"
#ifndef BITMAP_H
#define BITMAP_H


namespace ENGINE
{
	enum Pivot 
	{ 
		Center = 1 << 0,
		Left = 1 << 1, 
		Right = 1 << 2, 
		Top = 1 << 3, 
		Bottom = 1 << 4, 
	};

	class Bitmap
	{
	private:
		HDC memDC;
		HBITMAP hBitmap;
		SIZE origin, dest;
		RECT src;
		POINT pivot;
		INT pivotType;

	public:
		~Bitmap();
		// ��Ʈ�� �̹����� �ε��ϰ� �޸� DC�� �����.
		VOID Load(std::string name); 
		// ���� ȭ�鿡 ��µ� ũ�⸦ ����.
		VOID SetDrawSize(UINT width = 0U, UINT height = 0U); 
		// ȭ�鿡 ��µǴ� ũ�⸦ ���� ũ��� ����.
		VOID ResetSize() { dest = origin; }
		// Sprites �̹����� ������ ��ġ���� ������ ũ�⸸ŭ ���.
		VOID SliceSource(UINT cx, UINT cy, UINT width, UINT height)
		{
			src = { (LONG)cx, (LONG)cy, (LONG)width, (LONG)height };
		}
		VOID SetPivot(INT pivot);
		VOID ResetPivot() { pivot = { 0, 0 }; }
		// ���� �״�� ȭ�鿡 ���.
		BOOL BitBlt(INT32 x, INT32 y); 
		// ������ ��� ������� �����Ͽ� ���.
		BOOL StretchBlt(INT32 x, INT32 y); 
		// ������ ��� ������� �����ϰ� ���� ���� ���� ó���Ͽ� ���.
		BOOL TransparentBlt(INT32 x, INT32 y, UINT transparent = RGB(255, 0, 255));
		// ��� �̹��� ����ȭ
		BOOL AlphaBlendBlt(INT32 x, INT32 y, int transparency);// ���ϴ� ��(0 ~ 255)
		// ���� ��Ʈ���� ũ��.
		SIZE GetBitmapSize() CONST { return origin; } 
		// ȭ�鿡 ��µǴ� �̹����� ũ��.
		SIZE GetSize() CONST { return dest; } 
	}; // class Bitmap
}
#endif // !BITMAP_H