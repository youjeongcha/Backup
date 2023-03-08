#include "BitMap.h"
#pragma comment(lib, "msimg32.lib")

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, char* FileName)
{
	MemDC = CreateCompatibleDC(hdc); //�̹��� �ϳ��ϳ����� ���� ����
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //LR_LOADFROMFILE�� ���� �߿�. �̰͸� �־ �ȴ�
	
	SelectObject(MemDC, m_BitMap);

	BITMAP BitMap_Info; //�����Լ�. �˾Ƽ� �޸� �������.
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info); //BitMap�� �ּҸ� �޾ƿͼ�
	m_Size.cx = BitMap_Info.bmWidth; //�����Լ��� ���� ���θ� �˾Ƴ���
	m_Size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{//ī�� ũ�⸦ �ٲٸ� ���� ������ �̰͵� ���� �ٲ�� �� ��
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);
	TransparentBlt(hdc, x , y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	SelectObject(MemDC, OldBitmap);
}

void BitMap::DrawTransparent(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);
	BLENDFUNCTION bf;
	ZeroMemory(&bf, sizeof(bf));
	bf.SourceConstantAlpha = 190; //���ϴ� ��(0~255)
	AlphaBlend(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, bf);
	//TransparentBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
	SelectObject(MemDC, OldBitmap);
}

void BitMap::DrawBG(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{
	StretchBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

void BitMap::DrawSubWin(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{
	StretchBlt(hdc, x, y, IMG_WSize * 2, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

//void BitMap::DrawMove(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
//{
//	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);
//	BLENDFUNCTION bf;
//	ZeroMemory(&bf, sizeof(bf));
//	bf.SourceConstantAlpha = 100; //���ϴ� ��(0~255)
//	AlphaBlend(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, bf);
//	SelectObject(MemDC, OldBitmap);
//}

//void BitMap::DrawBackGroundIMG(HDC hdc)
//{
//	StretchBlt(hdc, 0, MAIN_Y, MAIN_W, MAIN_H, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY); //����� ��� 
//}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
