#include "Bitmap.h"
#include "SceneManager.h"

namespace ENGINE
{
	Bitmap::~Bitmap()
	{
		DeleteDC(memDC);
		DeleteObject(hBitmap);
	}

	VOID Bitmap::Load(std::string name)
	{
		memDC = CreateCompatibleDC(SceneMgr->GetBackDC()); //메모리 DC 생성
		hBitmap = (HBITMAP)LoadImageA(NULL, name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //비트맵 이미지 로드
		SelectObject(memDC, hBitmap);

		BITMAP BitMap;
		GetObject(hBitmap, sizeof(BITMAP), &BitMap); //비트맵의 정보 얻기
		origin.cx = BitMap.bmWidth; //비트맵의 원본 크기 저장.
		origin.cy = BitMap.bmHeight;
		dest = origin;
		src = { 0, 0, origin.cx, origin.cy }; //화면에 그려줄 크기와 rec를 원본 크기로 저장

		pivot = { 0,0 };
		pivotType = (Pivot::Left | Pivot::Top);
	}

	VOID Bitmap::SetDrawSize(UINT width, UINT height)
	{
		dest = { (long)width, (long)height };
		SetPivot(pivotType);
	}

	VOID Bitmap::SetPivot(INT pivot)
	{
		pivotType = pivot;

		int halfWidth = dest.cx * 0.5f;
		int halfHeigth = dest.cy * 0.5f;
		this->pivot = { -halfWidth, -halfHeigth };

		if (pivot & Pivot::Left)
			this->pivot.x += halfWidth;
		if (pivot & Pivot::Right)
			this->pivot.x += -halfWidth;
		if (pivot & Pivot::Top)
			this->pivot.y += halfHeigth;
		if (pivot & Pivot::Bottom)
			this->pivot.y += -halfHeigth;
	}

	BOOL Bitmap::BitBlt(INT32 x, INT32 y)
	{
		return ::BitBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, src.right, src.bottom, memDC, src.left, src.top, SRCCOPY);
	}

	BOOL Bitmap::StretchBlt(INT32 x, INT32 y)
	{
		return ::StretchBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, SRCCOPY);
	}

	BOOL Bitmap::TransparentBlt(INT32 x, INT32 y, UINT transparent)
	{
		return ::TransparentBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, transparent);
	}
	BOOL Bitmap::AlphaBlendBlt(INT32 x, INT32 y, int transparency)// 원하는 값(0 ~ 255)
	{
		BLENDFUNCTION bf;
		ZeroMemory(&bf, sizeof(bf));
		bf.SourceConstantAlpha = transparency; //값 0~ 255
		return ::AlphaBlend(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, bf);
	}
}