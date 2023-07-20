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
		// 비트맵 이미지를 로드하고 메모리 DC를 만든다.
		VOID Load(std::string name); 
		// 실제 화면에 출력될 크기를 변경.
		VOID SetDrawSize(UINT width = 0U, UINT height = 0U); 
		// 화면에 출력되는 크기를 원본 크기로 변경.
		VOID ResetSize() { dest = origin; }
		// Sprites 이미지의 임의의 위치부터 임의의 크기만큼 출력.
		VOID SliceSource(UINT cx, UINT cy, UINT width, UINT height)
		{
			src = { (LONG)cx, (LONG)cy, (LONG)width, (LONG)height };
		}
		VOID SetPivot(INT pivot);
		VOID ResetPivot() { pivot = { 0, 0 }; }
		// 원본 그대로 화면에 출력.
		BOOL BitBlt(INT32 x, INT32 y); 
		// 설정한 출력 사이즈로 변경하여 출력.
		BOOL StretchBlt(INT32 x, INT32 y); 
		// 설정한 출력 사이즈로 변경하고 지정 색을 투명 처리하여 출력.
		BOOL TransparentBlt(INT32 x, INT32 y, UINT transparent = RGB(255, 0, 255));
		// 출력 이미지 투명화
		BOOL AlphaBlendBlt(INT32 x, INT32 y, int transparency);// 원하는 값(0 ~ 255)
		// 원본 비트맵의 크기.
		SIZE GetBitmapSize() CONST { return origin; } 
		// 화면에 출력되는 이미지의 크기.
		SIZE GetSize() CONST { return dest; } 
	}; // class Bitmap
}
#endif // !BITMAP_H