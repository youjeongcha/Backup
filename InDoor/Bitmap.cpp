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
		memDC = CreateCompatibleDC(SceneMgr->GetBackDC()); //�޸� DC ����
		hBitmap = (HBITMAP)LoadImageA(NULL, name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //��Ʈ�� �̹��� �ε�
		SelectObject(memDC, hBitmap);

		BITMAP BitMap;
		GetObject(hBitmap, sizeof(BITMAP), &BitMap); //��Ʈ���� ���� ���
		origin.cx = BitMap.bmWidth; //��Ʈ���� ���� ũ�� ����.
		origin.cy = BitMap.bmHeight;
		dest = origin;
		src = { 0, 0, origin.cx, origin.cy }; //ȭ�鿡 �׷��� ũ��� rec�� ���� ũ��� ����

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
	BOOL Bitmap::AlphaBlendBlt(INT32 x, INT32 y, int transparency)// ���ϴ� ��(0 ~ 255)
	{
		BLENDFUNCTION bf;
		ZeroMemory(&bf, sizeof(bf));
		bf.SourceConstantAlpha = transparency; //�� 0~ 255
		return ::AlphaBlend(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, bf);
	}
}