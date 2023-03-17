#pragma once
#include "framework.h"
#include "BitMapManager.h"

enum UI_IMG_XYWH
{
	//타이틀
	IMG_TITLE_X = (int)(MAIN_W / 2.7f),
	IMG_TITLE_Y = MAIN_H / 7,
	IMG_TITLE_W = 200,
	IMG_TITLE_H = 100,

	//별 
	IMG_STAR_X,
	IMG_STAR_W,
	IMG_STAR_H,
	IMG_STAR_Y,

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
	IMG_POINT_X,
	IMG_POINT_W,
	IMG_POINT_H,
	IMG_POINT_Y,
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

class UI
{
private:
public:
	UI();
	~UI();

	//메뉴
	void DrawMenu(HDC hdc);
	void DrawTitle(HDC hdc);
	void UpdateStarFlow(float deltaTime);
	void DrawStarFlow(HDC hdc);
	void UpdateSelect(float deltaTime);
	void DrawSelect(HDC hdc);
	void DrawPoint(HDC hdc);

	//점수 + 목숨 창


	//미터
};

