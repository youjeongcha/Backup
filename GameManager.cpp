#include "GameManager.h"

#define PiecesMgr PiecesManager::Get_Instance()

GameManager* GameManager::m_pInstance = NULL; //초기화 필수

GameManager::GameManager()
{
	memset(m_Map, CAMP_NONE, sizeof(m_Map));
}

GameManager::~GameManager()
{
}


void GameManager::Init(BitMapManager* BitMapMgr_Main, HWND hWnd_Main)
{
	m_HWND_Main = hWnd_Main;
	//m_HWND_Sub = hWnd_Sub;

	m_BitMapMgr_Main = BitMapMgr_Main;
	//m_BitMapMgr_Sub = BitMapMgr_Sub;

	BitMapMgr_Main->Init(hWnd_Main);
	//BitMapMgr_Sub->Init(hWnd_Sub); //★원래 비트맵 Mgr 하나만 존재하는 게 맞는데. 간편하게 만들기 위해서 이번만 이렇게 사용

	PiecesMgr->Init(BitMapMgr_Main);
	//초기 map 상태를 CAMP로 초기화한다.
	for (int x = 0; x <= ONELINE_PIECES_COUNT; x++)
	{
		m_Map[x][0] = CAMP_BLACK;
		m_Map[x][1] = CAMP_BLACK;
		m_Map[x][6] = CAMP_WHITE;
		m_Map[x][7] = CAMP_WHITE;
	}
}

bool GameManager::ColliderCheck(POINT point)
{
	if (PiecesMgr->ColliderCheck(point))
		return true;
}

void GameManager::Draw(HDC hdc, HINSTANCE g_hInst)
{
	BoardDraw(hdc);

	PiecesMgr->DrawPices(hdc);
	//질문::불필요한 반복문 도는 거 막기?
	PiecesMgr->DrawMoveable(hdc);


	//std::wstring str;

	////글자 크기 변경
	//SelectObject(hdc, (HFONT)30);
	////oldfont = (HFONT)SelectObject(hdc, font);
	//SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	////SetBkColor(hdc, RGB(0, 0, 0));
	//SetTextColor(hdc, RGB(0, 250, 245)); //글자 색 변경


	//str = L"F O R E S T";
	//TextOut(hdc, 80, 80, str.c_str(), str.length());
}

void GameManager::MainMenu()
{
}

void GameManager::Game()
{
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
			if ( ((y & 1) == 0 && (x & 1) == 0) ||
				((y & 1) == 1 && (x & 1) == 1) )
				//x와 y가 둘다 짝수일 
				m_BitMapMgr_Main->GetImage(IMG::IMG_BG_WHITE)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
			else
				m_BitMapMgr_Main->GetImage(IMG::IMG_BG_BLACK)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		}
	}
}
