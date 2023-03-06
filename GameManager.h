#pragma once
#include "BitMapManager.h"
#include "PiecesManager.h"
#include <fstream>
#include <string>
#include <algorithm>

enum BOARD
{
	BOARD_X = 8,
	BOARD_Y = 8,

	BOARD_SQUARE_SIZE = 60, //사각형 하나의 크기

	BOARD_LINE = 10, //x,y 줄다 10개의 선이 필요
	BOARD_LINE_END = 8 * BOARD_SQUARE_SIZE,

};

enum FONTSIZE
{
	FONTSIZE_NUMBER,
	FONTSIZE_ORDER,
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND_Main;
	//HWND m_HWND_Sub;
	BitMapManager* m_BitMapMgr_Main;

	//BitMapManager* m_BitManpMgr_Sub;
	
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP m_Map[BOARD_X][BOARD_Y];

	GameManager();
	void MainMenu();
	void Game();

	//보드판 그리기
	void BoardDraw(HDC hdc);
	void LineDraw(HDC hdc);
	void SquareDraw(HDC hdc);
public:
	~GameManager();

	static GameManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new GameManager;
		return m_pInstance;
	}

	void Init(BitMapManager* BitMapMgr_Main, HWND hWnd_Main);
	bool ColliderCheck(POINT point);
	void Draw(HDC hdc, HINSTANCE g_hInst);
	//void SubDraw();

	HWND Get_HWND_Main() { return m_HWND_Main; }
	//void Set_Map(CAMP(*_Map())[BOARD_Y]) { (*m_Map)[BOARD_Y] = (*_Map())[BOARD_Y]; }
	void Set_Map(CAMP campColor, int x, int y) { m_Map[x][y] = campColor; }
	CAMP(*Get_Map())[BOARD_Y] { return m_Map; }
	//HWND Get_HWND_Sub() { return m_HWND_Sub; }
};
