#pragma once
#include "framework.h"
#include "BitMapManager.h"
//#include <list>
#include <vector>

#define STAR_SPEED 0.25
#define FLICKERING_SPEED 0.4

enum UI_IMG_XYWH
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


	//----------------���� + ��� â--------------------
	
	//���� â �׵θ�
	IMG_SCORE_OUTLINE_X = 100,
	IMG_SCORE_OUTLINE_Y = 20,
	IMG_SCORE_OUTLINE_W = MAIN_W - 200,
	IMG_SCORE_OUTLINE_H = 50,

	//����

	//���ʽ�

	//���
	IMG_Life_W = IMG_SCORE_OUTLINE_H / 3,
	IMG_Life_H = IMG_Life_W,
	IMG_Life_X = IMG_SCORE_OUTLINE_X + IMG_SCORE_OUTLINE_W - IMG_Life_W * 4,
	IMG_Life_Y = IMG_SCORE_OUTLINE_Y + IMG_SCORE_OUTLINE_H - IMG_Life_H - 10,
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

enum LIFE
{
	LIFE_MAX = 3,
};


class UI
{
private:
	//std::list<IMG> m_StarList;
	std::vector<IMG> m_StarList;
	float m_StarTime;
	int m_Point_Y;
	//Menu Select �̹��� �������� Ȯ���ϱ� ����
	float m_FlickeringTime;
	bool m_NotDrawCheck;
	float m_PointMoveTime;
	//���� ���
	int m_UserLife;

public:
	UI();
	~UI();

	//�޴�
	void DrawMenu(HDC hdc);
	void DrawTitle(HDC hdc);
	void UpdateStarFlow(float deltaTime);
	void DrawStarFlow(HDC hdc);
	void UpdateFlickering(float deltaTime);
	void DrawSelect(HDC hdc);
	void DrawPoint(HDC hdc);
	//Ű
	//�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
	bool KeyState_PointEnter();
	void KeyMove(int move_Y);

	//���� + ��� â
	void DrawScoreSpace(HDC hdc);
	void DrawScore(HDC hdc);
	void DrawBonus(HDC hdc);
	void DrawLife(HDC hdc);

	//����
	void DrawMeter(HDC hdc);
};

