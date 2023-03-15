#include "GameManager.h"
//★게임 종료는 GMMgr에서 관리
//★다음에는 font생성을 init에서 해서 멤버변수로 지니고 있는다.

#define PiecesMgr PiecesManager::Get_Instance()

GameManager* GameManager::m_pInstance = NULL; //초기화 필수

GameManager::GameManager()
{
	memset(m_Map, CAMP_NONE, sizeof(m_Map));
	m_PlayerTurn = CAMP_WHITE;
	m_GameStopCheck = false;
	m_GameEndCheck = false;
}

GameManager::~GameManager()
{
}


void GameManager::Init(HWND hWnd_Main, HWND hWnd_Sub, int _nCmdShow, LPCTSTR _IpszClassSub_Promotion, HINSTANCE _hInstance)
{
	m_HWND_Main = hWnd_Main;
	m_HWND_Sub = hWnd_Sub;

	nCmdShow = _nCmdShow;
	IpszClassSub_Promotion = _IpszClassSub_Promotion;
	hInstance = _hInstance;

	BitMapMgr->Init(hWnd_Main);
	PiecesMgr->Init(BitMapMgr);

	//BitMapMgr_Main->Init(hWnd_Main);
	//BitMapMgr_Sub->Init(hWnd_Sub); //★원래 비트맵 Mgr 하나만 존재하는 게 맞는데. 간편하게 만들기 위해서 이번만 이렇게 사용


	//초기 map 상태를 CAMP로 초기화한다.
	for (int x = 0; x <= ONELINE_PIECES_COUNT; x++)
	{
		m_Map[x][0] = CAMP_BLACK;
		m_Map[x][1] = CAMP_BLACK;
		m_Map[x][6] = CAMP_WHITE;
		m_Map[x][7] = CAMP_WHITE;
	}

	exitRect.left = RECT_EXIT_L;
	exitRect.top = RECT_EXIT_T;
	exitRect.right = RECT_EXIT_R;
	exitRect.bottom = RECT_EXIT_B;

	//더블 버퍼링
	HDC hdc = GetDC(hWnd_Main);
	backDC_Main = CreateCompatibleDC(hdc);
	GetClientRect(m_HWND_Main, &clientRect_Main);

	hdc = GetDC(hWnd_Sub);
	backDC_Sub = CreateCompatibleDC(hdc);	
	GetClientRect(m_HWND_Sub, &clientRect_Sub);


	ReleaseDC(hWnd_Main, hdc);
}


bool GameManager::ColliderCheck(POINT point)
{
	if (m_GameStopCheck == false)
	{
		if (PiecesMgr->ColliderCheck(point))
			return true;
	}
	else
	{
		if (m_GameEndCheck == true)
		{
			//게임 오버되었을때만 exitRect가 뜨고 실행된다.
			if (PtInRect(&exitRect, point))
				PostQuitMessage(0);
		}
		return false;
	}
}

bool GameManager::ColliderCheck_SubPromotion(POINT point)
{
	if ((m_GameStopCheck == true) && (m_GameEndCheck == false))
	{
		//승진 Piece 선택한 경우
		if (PiecesMgr->ColliderCheck_SubPromotion(point))
		{
			m_GameStopCheck = false;
			InvalidateRect(m_HWND_Main, NULL, false);

			return true;
		}
	}
	return false;
}



void GameManager::Draw(HDC hdc, HINSTANCE g_hInst)
{
	//---------더블버퍼링----------
	//RECT clientRect;
	//GetClientRect(m_HWND_Main, &clientRect);
	
	HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect_Main.right + 1, clientRect_Main.bottom + 1);
	SelectObject(backDC_Main, backBitmap);

	//------------------------------

	BoardDraw(backDC_Main);

	PiecesMgr->DrawPices(backDC_Main);
	//질문::불필요한 반복문 도는 거 막기?
	PiecesMgr->DrawMoveable(backDC_Main);

	//게임 승리시 처리
	WinCheck(backDC_Main);

	//---------더블버퍼링----------
	BitBlt(hdc, 0, 0, clientRect_Main.right + 1, clientRect_Main.bottom + 1, backDC_Main, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

void GameManager::BoardDraw(HDC hdc)
{
	SquareDraw(hdc);
	LineDraw(hdc);
}

void GameManager::LineDraw(HDC hdc)
{
	for (int x = 0; x <= BOARD_X; x++)
	{
		MoveToEx(hdc, x * BOARD_SQUARE_SIZE, 0, NULL);
		LineTo(hdc, x * BOARD_SQUARE_SIZE, BOARD_LINE_END);
	}

	for (int y = 0; y <= BOARD_Y; y++)
	{
		MoveToEx(hdc, 0, y * BOARD_SQUARE_SIZE, NULL);
		LineTo(hdc, BOARD_LINE_END, y * BOARD_SQUARE_SIZE);
	}
}

void GameManager::SquareDraw(HDC hdc)
{
	for (int x = 0; x <= BOARD_X; x++)
	{
		for (int y = 0; y <= BOARD_Y; y++)
		{
			if (((y & 1) == 0 && (x & 1) == 0) ||
				((y & 1) == 1 && (x & 1) == 1))
				//x와 y가 둘다 짝수일 
				BitMapMgr->GetImage(IMG::IMG_BG_WHITE)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
			else
				BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		}
	}
}



void GameManager::WinCheck(HDC hdc)
{
	if (m_GameEndCheck)
	{
		std::wstring str;
		HFONT font;

		//검은 이미지 투명도 높여서 게임이 끝남을 알림
		BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawTransparent(hdc, 0, 0, BOARD_SQUARE_SIZE * BOARD_X, BOARD_SQUARE_SIZE * BOARD_Y);

		//글자 크기 변경
		font = CreateFont(VICTORY_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
		//SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경

		switch (m_PlayerTurn)
		{
		case CAMP_BLACK:
			str = L"B L A C K";
			break;
		case CAMP_WHITE:
			str = L"W H I T E";
			break;
		}

		str += L"  W I N";
		TextOut(hdc, RECT_EXIT_L - 32, MAIN_H / 3 + 10, str.c_str(), str.length());

		font = CreateFont(END_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		SelectObject(hdc, font);
		str = L"E n d";
		DrawText(hdc, str.c_str(), str.length(), &exitRect, DT_CENTER | DT_WORDBREAK);
	}
}



void GameManager::SubDraw(HDC hdc)
{
	//---------더블버퍼링----------
	HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect_Sub.right + 1, clientRect_Sub.bottom + 1);
	SelectObject(backDC_Sub, backBitmap);

	//------------------------------
	switch (m_PlayerTurn)
	{
	case CAMP_BLACK:
		BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawSubWin(backDC_Sub, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		break;
	case CAMP_WHITE:
		BitMapMgr->GetImage(IMG::IMG_BG_WHITE)->DrawSubWin(backDC_Sub, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		break;
	}

	//---------더블버퍼링----------
	BitBlt(hdc, 0, 0, clientRect_Sub.right + 1, clientRect_Sub.bottom + 1, backDC_Sub, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

void GameManager::SubPromotionDraw(HDC hdc)
{
	//---------더블버퍼링----------
	HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect_Sub_Promotion.right + 1, clientRect_Sub_Promotion.bottom + 1);
	SelectObject(backDC_Sub_Promotion, backBitmap);

	//------------------------------
	if ((m_GameStopCheck == true) && (m_GameEndCheck == false))
		PiecesMgr->DrawPawnPromotion(backDC_Sub_Promotion);

	//---------더블버퍼링----------
	BitBlt(hdc, 0, 0, clientRect_Sub_Promotion.right + 1, clientRect_Sub_Promotion.bottom + 1, backDC_Sub_Promotion, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

void GameManager::SubPromotion()
{
	//서브 일정 단계가 지나고 출력하도록(Pawn 승진)
	m_HWND_Sub_Promotion = CreateWindow(IpszClassSub_Promotion, IpszClassSub_Promotion, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_PROMOTION_X, SUB_PROMOTION_Y, SUB_PROMOTION_W, SUB_PROMOTION_H,
		NULL, (HMENU)NULL, hInstance, NULL);

	HDC hdc = GetDC(m_HWND_Sub_Promotion);
	backDC_Sub_Promotion = CreateCompatibleDC(hdc);
	GetClientRect(m_HWND_Sub_Promotion, &clientRect_Sub_Promotion);

	ReleaseDC(m_HWND_Sub_Promotion, hdc);

	ShowWindow(m_HWND_Sub_Promotion, nCmdShow);
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