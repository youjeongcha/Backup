#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	ReleaseDC(m_HWND, m_fDC);
	ReleaseDC(m_HWND, m_bDC);
}

void GameManager::init(HWND hWnd)
{
	m_HWND = hWnd;
	m_fDC = GetDC(m_HWND);
	m_bDC = GetDC(m_HWND);

	BitMapMgr->Init(hWnd);
}

void GameManager::Update(float deltaTime)
{
	m_mDraw.UpdateSpectator(deltaTime);
}

void GameManager::Draw()
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_fDC, m_clientRect.right + 1, m_clientRect.bottom + 1);
	SelectObject(m_bDC, backBitmap);

	//잔디
	m_mDraw.DrawGrass(m_bDC);
	m_mDraw.DrawSpectator(m_bDC);

	//더블 버퍼링
	BitBlt(m_fDC, 0, 0, m_clientRect.right + 1, m_clientRect.bottom + 1, m_bDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}


//더블 버퍼링
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
	bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
	bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}