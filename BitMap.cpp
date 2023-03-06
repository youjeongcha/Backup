#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, char* FileName)
{
	MemDC = CreateCompatibleDC(hdc); //이미지 하나하나마다 따로 관리
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //LR_LOADFROMFILE이 제일 중요. 이것만 있어도 된다
	SelectObject(MemDC, m_BitMap); //OldBitmap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP BitMap_Info; //지역함수. 알아서 메모리 사라진다.
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info); //BitMap의 주소를 받아와서
	m_Size.cx = BitMap_Info.bmWidth; //내장함수로 가로 세로를 알아낸다
	m_Size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, int IMG_WSize, int IMG_HSize)
{//카드 크기를 바꾸면 선택 영역인 이것도 같이 바꿔야 할 것
	StretchBlt(hdc, x, y, IMG_WSize, IMG_HSize, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
	//TODO::0.05f하면 출력되는 이미지 마다 다 작아지니. 출력할 크기의 인자를 받아오는 쪽으로 
}

void BitMap::DrawBackGroundIMG(HDC hdc)
{
	StretchBlt(hdc, 0, MAIN_Y, MAIN_W, MAIN_H, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY); //복사및 출력 
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
