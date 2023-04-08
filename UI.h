#pragma once
#include <vector>
#include <string>
#include "framework.h"
#include "BitMapManager.h"

#define STAR_SPEED 0.25
#define FLICKERING_SPEED 0.4
#define POINT_SPEED 0.12
#define BONUS_SPEED 0.1

enum UI_IMG_XYWH //UI ���� �̹����� ����
{
	//Ÿ��Ʋ
	IMG_TITLE_X = (int)(MAIN_W / 2.7f),
	IMG_TITLE_Y = MAIN_H / 7,
	IMG_TITLE_W = 200,
	IMG_TITLE_H = 100,

	//��(TOP�� ���� ù��° ���� �������� �Ѵ�.)
	IMG_STAR_X = IMG_TITLE_X - 60,
	IMG_STAR_Y = IMG_TITLE_Y - 20,
	IMG_STAR_W = 18,
	IMG_STAR_H = IMG_STAR_W,

	//������
	IMG_SELECT_X = IMG_TITLE_X - 10,
	IMG_SELECT_Y = IMG_TITLE_Y + 170,
	IMG_SELECT_W = IMG_TITLE_W + 10,
	IMG_SELECT_H = 40,
	//1 PLAYER A ~ 2 PLAYERS B
	IMG_SELECT_PLAYER_X = IMG_SELECT_X + 20, //�鿩���� �� ���� ����
	IMG_SELECT_PLAYER_Y = IMG_SELECT_Y + 40,
	IMG_SELECT_PLAYER_W = IMG_SELECT_W - 40,
	IMG_SELECT_PLAYER_H = 20,

	//����Ʈ
	IMG_POINT_X = IMG_SELECT_PLAYER_X - 40,
	IMG_POINT_Y = IMG_SELECT_PLAYER_Y,
	IMG_POINT_W = 30,
	IMG_POINT_H = 20,

	IMG_POINT_MAX_Y = IMG_POINT_Y + IMG_POINT_H * 3,


	//----------------���� â + ��� â--------------------
	
	//���� â �׵θ�
	//IMG_SCORE_OUTLINE_X = 100,
	//IMG_SCORE_OUTLINE_Y = 20,
	//IMG_SCORE_OUTLINE_W = MAIN_W - 200,
	//IMG_SCORE_OUTLINE_H = 50,

	//���� â �׵θ�
	IMG_SCORE_OUTLINE_X = 150,
	IMG_SCORE_OUTLINE_Y = 20,
	IMG_SCORE_OUTLINE_W = MAIN_W - 300,
	IMG_SCORE_OUTLINE_H = 50,

	//���
	IMG_Life_W = IMG_SCORE_OUTLINE_H / 3,
	IMG_Life_H = IMG_Life_W,
	IMG_Life_X = IMG_SCORE_OUTLINE_X + IMG_SCORE_OUTLINE_W - IMG_Life_W * 4,
	IMG_Life_Y = IMG_SCORE_OUTLINE_Y + IMG_SCORE_OUTLINE_H - IMG_Life_H - 10,
};

enum FONT //��Ʈ ����
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

	//1�� ����
	STAR_TOP = 16,
	STAR_RIGHT = 22,
	STAR_BOTTOM = 38,
	STAR_LEFT = 44,
};

//-----------Ű---------------
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
	//Menu Select �̹��� �������� Ȯ���ϱ� ����
	float m_FlickeringTime;
	bool m_NotDrawCheck;
	//������ �̵�
	float m_PointMoveTime;
	////���� ���
	//int m_UserLife;
	//����
	float m_ScoreTime;
	int m_Score;
	int m_Bonus;


	//���θ޴�------------------------------------
	//Draw
	void DrawTitle(HDC hdc);		//Ÿ��Ʋ
	void DrawStarFlow(HDC hdc);		//��
	void DrawSelect(HDC hdc);		//������
	void DrawPoint(HDC hdc);		//������
	//Update
	void UpdateStarFlow(float deltaTime);
	void UpdateFlickering(float deltaTime);
	bool UpdateKeyState_Enter(float deltaTime);	//Ű		//�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
	//Ű
	void KeyMoveSelect(int move_Y);


	//����-----------------------------------------
	void DrawScoreSpace(HDC hdc);	//�������̽� â
	void DrawScore(HDC hdc);		//����
	void DrawLife(HDC hdc);			//���
	//Update
	void UpdateBonus(float deltaTime);

public:
	UI();
	~UI();

	//�ʱ� ����
	void InitialSet(SET setType);

	//�޴�------------------------------
	void DrawMenu(HDC hdc);
	bool UpdateMenu(float deltaTime);


	//����------------------------------
	void DrawGame(HDC hdc);
	void UpdateGame(float deltaTime);

	//���� ����
	void ScoreUp() { m_Score += 100; }
};

