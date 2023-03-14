#pragma once
#include "BitMapManager.h"
#include "PiecesManager.h"
#include <fstream>
#include <string>
#include <algorithm>

//★ 여기에 기록해두고 중복 선언 없이 사용
#define GMMgr GameManager::Get_Instance()
#define PiecesMgr PiecesManager::Get_Instance()
#define BitMapMgr BitMapManager::GetInstance()

enum BOARD
{
	BOARD_X = 8,
	BOARD_Y = 8,

	BOARD_SQUARE_SIZE = 60, //사각형 하나의 크기
	//BOARD_SQUARE_Sub_SIZE = 120, //Sub Window 띄우기 위한 크기

	BOARD_LINE = 10, //x,y 줄다 10개의 선이 필요
	BOARD_LINE_END = 8 * BOARD_SQUARE_SIZE,

};

enum FONTSIZE
{
	FONTSIZE_NUMBER,
	FONTSIZE_ORDER,
};

enum FONT
{
	VICTORY_FONTSIZE = 15,
	END_FONTSIZE = 13,
	//END_FONTSIZE = 20,

	RECT_EXIT_L = 210,
	RECT_EXIT_T = 250,
	RECT_EXIT_R = RECT_EXIT_L + 60,
	//RECT_EXIT_R = RECT_EXIT_L + 30,
	RECT_EXIT_B = RECT_EXIT_T + 30,
	//RECT_EXIT_B = RECT_EXIT_T + 15,
};


class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND_Main;
	HWND m_HWND_Sub;
	HWND m_HWND_Sub_Promotion;
	//★ BitMapManager로써의 의미가 퇴색되었다. 싱글톤으로 만들어서 사용하는 것을 권장. main이나 sub나 인자를 넣어서(?) 해당 BitMapManager를 사용하도록
	//BitMapManager* m_BitMapMgr_Main;
	//BitMapManager* m_BitMapMgr_Sub;
	//BitMapManager* m_BitMapMgr_Sub_Promotion;

	//SubPromotion 등록하기 위해
	int nCmdShow;
	LPCTSTR IpszClassSub_Promotion;
	HINSTANCE hInstance;
	
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP m_Map[BOARD_X][BOARD_Y];
	//현재 플레이어 턴 확인
	CAMP m_PlayerTurn;
	bool m_GameStopCheck;
	bool m_GameEndCheck;
	RECT exitRect; //메인

	GameManager();

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

	//void Init(BitMapManager* BitMapMgr_Main, BitMapManager* BitMapMgr_Sub, BitMapManager* BitMapMgr_Sub_Promtion, HWND hWnd_Main, HWND hWnd_Sub, int nCmdShow, LPCTSTR IpszClassSub_Promotion, HINSTANCE hInstance);
	void Init(HWND hWnd_Main, HWND hWnd_Sub, int nCmdShow, LPCTSTR IpszClassSub_Promotion, HINSTANCE hInstance);
	bool ColliderCheck(POINT point);
	bool ColliderCheck_SubPromotion(POINT point);
	void Draw(HDC hdc, HINSTANCE g_hInst);
	void WinCheck(HDC hdc);
	void SubDraw(HDC hdc);
	void SubPromotionDraw(HDC hdc);
	void SubPromotion();

	HWND Get_HWND_Main() { return m_HWND_Main; }
	HWND Get_HWND_Sub() { return m_HWND_Sub; }
	HWND Get_HWND_Sub_Promotion() { return m_HWND_Sub_Promotion; }

	CAMP(*Get_Map())[BOARD_Y] { return m_Map; }
	//BitMapManager* Get_BitMapMain() { return m_BitMapMgr_Main; }
	CAMP Get_PlayerTurn() { return m_PlayerTurn; }
	bool Get_GameStopCheck() { return m_GameStopCheck; }
	bool Get_GameEndCheck() { return m_GameEndCheck; }

	void Set_Map(CAMP campColor, int x, int y) { m_Map[x][y] = campColor; }
	//현재 턴과 반대되는 턴을 세팅해준다.
	void Set_PlayerTurn() { m_PlayerTurn = (m_PlayerTurn == CAMP_WHITE) ? CAMP_BLACK : CAMP_WHITE; }
	void Set_GameStopCheck(bool check) { m_GameStopCheck = check; }
	void Set_GameEndCheck(bool check) { m_GameEndCheck = check; }
};
