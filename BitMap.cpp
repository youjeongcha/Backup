#include "BitMap.h"

BitMap::BitMap()
{
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}

void BitMap::Init(HDC hdc, char* FileName)
{
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	MemDC = CreateCompatibleDC(hdc); //�̹��� �ϳ��ϳ����� ���� ����
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //LR_LOADFROMFILE�� ���� �߿�. �̰͸� �־ �ȴ�
	SelectObject(MemDC, m_BitMap); //OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP BitMap_Info; //�����Լ�. �˾Ƽ� �޸� �������.
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info); //BitMap�� �ּҸ� �޾ƿͼ�
	m_Size.cx = BitMap_Info.bmWidth; //�����Լ��� ���� ���θ� �˾Ƴ���
	m_Size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize)
{//ī�� ũ�⸦ �ٲٸ� ���� ������ �̰͵� ���� �ٲ�� �� ��
	StretchBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
	//TODO::0.05f�ϸ� ��µǴ� �̹��� ���� �� �۾�����. ����� ũ���� ���ڸ� �޾ƿ��� ������ 
}

void BitMap::DrawTransparent(HDC hdc, float x, float y, float IMG_WSize, float IMG_HSize)
{
	TransparentBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));

	//BLENDFUNCTION bf;
	//ZeroMemory(&bf, sizeof(bf));
	//bf.SourceConstantAlpha = 190; //���ϴ� ��(0~255)
	//AlphaBlend(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, bf);
}