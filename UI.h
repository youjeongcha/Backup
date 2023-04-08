#pragma once
#include <vector>
#include <string>
#include "framework.h"
#include "BitMapManager.h"

#define STAR_SPEED 0.25
#define FLICKERING_SPEED 0.4
#define POINT_SPEED 0.12
#define BONUS_SPEED 0.1

enum UI_IMG_XYWH //UI 관련 이미지만 관리
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


	//----------------점수 창 + 목숨 창--------------------
	
	//점수 창 테두리
	//IMG_SCORE_OUTLINE_X = 100,
	//IMG_SCORE_OUTLINE_Y = 20,
	//IMG_SCORE_OUTLINE_W = MAIN_W - 200,
	//IMG_SCORE_OUTLINE_H = 50,

	//점수 창 테두리
	IMG_SCORE_OUTLINE_X = 150,
	IMG_SCORE_OUTLINE_Y = 20,
	IMG_SCORE_OUTLINE_W = MAIN_W - 300,
	IMG_SCORE_OUTLINE_H = 50,

	//목숨
	IMG_Life_W = IMG_SCORE_OUTLINE_H / 3,
	IMG_Life_H = IMG_Life_W,
	IMG_Life_X = IMG_SCORE_OUTLINE_X + IMG_SCORE_OUTLINE_W - IMG_Life_W * 4,
	IMG_Life_Y = IMG_SCORE_OUTLINE_Y + IMG_SCORE_OUTLINE_H - IMG_Life_H - 10,
};

enum FONT //폰트 관련
{
	FONT_STAGE = 0,
	FONT_SCORE,
	FONT_COUNT,

	FONT_STAGE_SIZE = 16,
	FONT_STAGE_X = IMG_SCORE_OUTLINE_X + 15,
	FONT_STAGE_Y = IMG_SCORE_OUTLINE_Y + 11,

	FONT_SCORE_SIZE = 18,
	FONT_SCORE_X = IMG_SCORE_OUTLINE_X + 180,
	FONT_SCORE_Y = IMG_SCORE_OUTLINE_Y + 15,

	FONT_BONUS_X = FONT_SCORE_X + 150,
	FONT_BONUS_Y = FONT_SCORE_Y,

	FONT_BONUS_COUNTING_X = FONT_BONUS_X + FONT_SCORE_SIZE * 3 + 10,

};

enum SCORE
{
	SCORE_START = 0,
	SCORE_BONUS = 10000,

	SCORE_BONUS_REDUTION = 10,
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
	std::vector<IMG> m_StarIMG_List;
	std::vector<POINT> m_StarXY_List;
	float m_StarTime;
	int m_Point_Y;
	//Menu Select 이미지 깜빡일지 확인하기 위해
	float m_FlickeringTime;
	bool m_NotDrawCheck;
	//선택지 이동
	float m_PointMoveTime;
	////유저 목숨
	//int m_UserLife;
	//점수
	float m_ScoreTime;
	int m_Score;
	int m_Bonus;


	//메인메뉴------------------------------------
	//Draw
	void DrawTitle(HDC hdc);		//타이틀
	void DrawStarFlow(HDC hdc);		//별
	void DrawSelect(HDC hdc);		//선택지
	void DrawPoint(HDC hdc);		//포인터
	//Update
	void UpdateStarFlow(float deltaTime);
	void UpdateFlickering(float deltaTime);
	bool UpdateKeyState_Enter(float deltaTime);	//키		//함수를 bool형으로 UI안에서 해결한다.
	//키
	void KeyMoveSelect(int move_Y);


	//게임-----------------------------------------
	void DrawScoreSpace(HDC hdc);	//인터페이스 창
	void DrawScore(HDC hdc);		//점수
	void DrawLife(HDC hdc);			//목숨
	//Update
	void UpdateBonus(float deltaTime);

public:
	UI();
	~UI();

	//초기 세팅
	void InitialSet(SET setType);

	//메뉴------------------------------
	void DrawMenu(HDC hdc);
	bool UpdateMenu(float deltaTime);


	//게임------------------------------
	void DrawGame(HDC hdc);
	void UpdateGame(float deltaTime);

	//점수 증가
	void ScoreUp() { m_Score += 100; }
};

