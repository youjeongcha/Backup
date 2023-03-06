#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, char* FileName)
{
	MemDC = CreateCompatibleDC(hdc); //�̹��� �ϳ��ϳ����� ���� ����
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //LR_LOADFROMFILE�� ���� �߿�. �̰͸� �־ �ȴ�
	SelectObject(MemDC, m_BitMap); //OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP BitMap_Info; //�����Լ�. �˾Ƽ� �޸� �������.
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info); //BitMap�� �ּҸ� �޾ƿͼ�
	m_Size.cx = BitMap_Info.bmWidth; //�����Լ��� ���� ���θ� �˾Ƴ���
	m_Size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{//ī�� ũ�⸦ �ٲٸ� ���� ������ �̰͵� ���� �ٲ�� �� ��
	StretchBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
	//TODO::0.05f�ϸ� ��µǴ� �̹��� ���� �� �۾�����. ����� ũ���� ���ڸ� �޾ƿ��� ������ 
}

void BitMap::DrawBackGroundIMG(HDC hdc)
{
	StretchBlt(hdc, 0, MAIN_Y, MAIN_W, MAIN_H, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY); //����� ��� 
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
