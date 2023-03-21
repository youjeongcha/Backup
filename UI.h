#pragma once
#include "framework.h"
#include "BitMapManager.h"
#include <list>

#define STAR_SPEED 0.25
#define FLICKERING_SPEED 0.4

enum UI_IMG_XYWH
{
	//타이틀
	IMG_TITLE_X = (int)(MAIN_W / 2.7f),
	IMG_TITLE_Y = MAIN_H / 7,
	IMG_TITLE_W = 200,
	IMG_TITLE_H = 100,

	//별(TOP의 왼쪽 첫번째 별을 기준으로 한다.)
	IMG_STAR_X = IMG_TITLE_X - 60,
	IMG_STAR_Y = IMG_TITLE_Y - 20,
	IMG_STAR_W = 18,
	IMG_STAR_H = IMG_STAR_W,

	//선택지
	IMG_SELECT_X = IMG_TITLE_X - 10,
	IMG_SELECT_Y = IMG_TITLE_Y + 170,
	IMG_SELECT_W = IMG_TITLE_W + 10,
	IMG_SELECT_H = 40,
	//1 PLAYER A ~ 2 PLAYERS B
	IMG_SELECT_PLAYER_X = IMG_SELECT_X + 20, //들여쓰기 빈 공간 위해
	IMG_SELECT_PLAYER_Y = IMG_SELECT_Y + 40,
	IMG_SELECT_PLAYER_W = IMG_SELECT_W - 40,
	IMG_SELECT_PLAYER_H = 20,

	//포인트
	IMG_POINT_X = IMG_SELECT_PLAYER_X - 40,
	IMG_POINT_Y = IMG_SELECT_PLAYER_Y,
	IMG_POINT_W = 30,
	IMG_POINT_H = 20,

	IMG_POINT_MAX_Y = IMG_POINT_Y + IMG_POINT_H * 3,


	//----------------점수 + 목숨 창--------------------
	IMG_SCORE_OUTLINE_X = 50,
	IMG_SCORE_OUTLINE_Y = 20,
	IMG_SCORE_OUTLINE_W = MAIN_W - 100,
	IMG_SCORE_OUTLINE_H = 50,
};

enum SELECT_PLAYER
{
	SELECT_PLAYER_START,
	SELECT_PLAYER_1A = SELECT_PLAYER_START,
	SELECT_PLAYER_1B,
	SELECT_PLAYER_2A,
	SELECT_PLAYER_2B,
	SELECT_PLAYER_COUNT,
};

enum STAR
{
	STAR_START = 0,
	STAR_RED = STAR_START,
	STAR_YELLOW,
	STAR_BLUE,
	STAR_END = STAR_BLUE,
	STAR_TOTAL_COUNT = 44,

	//1줄 가로
	STAR_TOP = 16,
	STAR_RIGHT = 22,
	STAR_BOTTOM = 38,
	STAR_LEFT = 44,
};

//-----------키---------------
enum MENU_KEY
{
	MENU_KEY_UP = -1,
	MENU_KEY_DOWN = 1,
};


class UI
{
private:
	std::list<IMG> m_StarList;
	float m_StarTime;
	int m_Point_Y;
	//Menu Select 이미지 깜빡일지 확인하기 위해
	float m_FlickeringTime;
	bool m_NotDrawCheck;
	float m_PointMoveTime;

public:
	UI();
	~UI();

	//메뉴
	void DrawMenu(HDC hdc);
	void DrawTitle(HDC hdc);
	void UpdateStarFlow(float deltaTime);
	void DrawStarFlow(HDC hdc);
	void UpdateFlickering(float deltaTime);
	void DrawSelect(HDC hdc);
	//void DrawSelectBlack(HDC hdc);
	void DrawPoint(HDC hdc);
	//키
	bool KeyState_PointEnter();
	void KeyMove(int move_Y);

	//점수 + 목숨 창
	void DrawScoreSpace(HDC hdc);
	void DrawScore(HDC hdc);
	void DrawBonus(HDC hdc);
	void DrawLife(HDC hdc);
	void DrawStage(HDC hdc);

	//미터
	void DrawMeter(HDC hdc);
};

