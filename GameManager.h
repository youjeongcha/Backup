#pragma once
#include "CardManager.h"
#include "BitMapManager.h"
#include <string>
#include <fstream>
#include <map>


enum MENUCLICK
{
	MENUCLICK_X = int(MAIN_W * 0.33),
	MENUCLICK_Y = int(MAIN_H * 0.32),
};

enum FONT
{
	FONT_GAMENAME,
	FONT_START_EXIT,
	FONT_STORY,
	FONT_NEXT,
	FONT_CLOCK,
	FONT_GAMECLEAR,

	FONT_COUNT,
};

enum FONTSIZE
{
	FONTSIZE_GAMENAME = 50,
	FONTSIZE_START_EXIT = 18,
	FONTSIZE_STORY = 14,
	FONTSIZE_NEXT = 15,
	FONTSIZE_CLOCK = 25,
	FONTSIZE_GAMECLEAR = 25,
};

enum RECTRANGE
{
	RECT_START_L = MENUCLICK_X + 100,
	RECT_START_T = MENUCLICK_Y + 100,
	RECT_START_R = RECT_START_L + 80,
	RECT_START_B = RECT_START_T + FONTSIZE_START_EXIT,
	
	RECT_EXIT_L = RECT_START_L,
	RECT_EXIT_T = RECT_START_T + 40,
	RECT_EXIT_R = RECT_EXIT_L + 80,
	RECT_EXIT_B = RECT_EXIT_T + FONTSIZE_START_EXIT,

	RECT_NEXT_L = MAIN_W - 120,
	RECT_NEXT_T = MAIN_H - 80,
	RECT_NEXT_R = MAIN_W,
	RECT_NEXT_B = MAIN_H,
	
	RECT_Timer_L = MAIN_W - 140,
	RECT_Timer_T = MAIN_Y + 10,
	RECT_Timer_R = MAIN_W,
	RECT_Timer_B = MAIN_Y + 50,
};


enum SEC
{
	SEC_SCENE_SHOWCARD = 5, //카드 순서 보여주기 씬 5초
	SEC_SCENE_CARDGMAE = 40, //TODO::임시. 카드 게임 60초
	SEC_SCENE_GAMEOVERE = 2,

	//감소 시간
	SEC_MINUS = 2,
	SEC_MINUS_PRINT_X = RECT_Timer_L + 10,
	SEC_MINUS_PRINT_Y = RECT_Timer_T + FONTSIZE_CLOCK,
	SEC_MINUS_PRINT = 1,

	//이미지 변환 시점
	SEC_CHANGE_IMG = 10,
};

enum STORY
{
	STORY_INTRO,
	STORY_RABBIT,
	STORY_CLEAR,

	STORY_INTRO_LINE = 12,
	STORY_INTRO_X = MENUCLICK_X,
	STORY_INTRO_Y = 160,

	STORY_RABBIT_LINE = 7,
	STORY_RABBIT_X = MENUCLICK_X + 80,
	STORY_RABBIT_Y = 20,
	
	STORY_CLEAR_LINE = 2,
	STORY_CLEAR_X = MENUCLICK_X + 120,
	STORY_CLEAR_Y = MAIN_H - 200,

	STORY_ADVICE_Y = 140
};

struct XY
{
	float X;
	float Y;
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND_Main;
	HWND m_HWND_Sub;
	BitMapManager* m_BitMapMgr_Main;
	BitMapManager* m_BitMapMgr_Sub;

	//LATER::RECT 배열로 정리
	RECT startRect; //메인
	RECT exitRect; //메인
	RECT nextRect; //스토리
	RECT timerRect; //가시적 타이머

	HFONT font[FONT_COUNT]; //글자 크기 변경
	XY click;
	SEQUENCE scene;

	int second; //반복으로 카운트 +1 해서 sec 체크
	int keep_sec; //감소 표시 일정 시간 띄워두기 위해
	bool cardSame; //2개의 카드가 다른 경우 2초 감소 Print를 위해
	int changeIMG_Sec; //이미지 변경할 초
	std::wstring strSec;
	std::map<STORY, std::vector<std::string>> storyList; //★ into,stage, gameOver를 enum으로 판단해서. 백터 배열로 호출해서 사용 

	GameManager();
	void MainMenu(HDC hdc, HINSTANCE g_hInst);
	void Story(HDC hdc, STORY storyType, STORY storyLine, STORY x, STORY y);
	void GameClear(HDC hdc);
	void GameOver(HDC hdc);

	void LoadStory();
	void PrintAdvice(HDC hdc);
	void PrintTimer(HDC hdc, std::wstring wstrSec);


public:
	~GameManager();

	static GameManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new GameManager;
		return m_pInstance;
	}

	void Init(BitMapManager* BitMapMgr_Main, BitMapManager* BitMapMgr_Sub, HWND hWnd_Main, HWND hWnd_Sub);
	bool ColliderCheck(POINT Point);
	//Draw 함수로 GM에서 switch문 처리
	void Draw(HDC hdc, HINSTANCE g_hInst);
	//WPARAM이 타이머의 ID값을 구분한다. //ture면 InvalidateRect + 타이머 시간 변경 위해 함수 안에서고 InvalidateRect
	bool Timer(WPARAM wParam);
	void SubDraw(HDC hdc);
	void Kill_AllTimer();

	SEQUENCE Get_Scene() { return scene; };
	HWND Get_HWND_Main() { return m_HWND_Main; }
	HWND Get_HWND_Sub() { return m_HWND_Sub; }
};

