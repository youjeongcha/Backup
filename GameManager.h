#pragma once
#include <vector>
#include <time.h>
#include "framework.h"
#include "Circle.h"
#include "Box.h"

#define GMMgr GameManager::Get_Instance()

#define CREATE_SEC 5

enum WindowXY
{
	MAIN_X = 200,
	MAIN_Y = 100,
	MAIN_W = 450,
	MAIN_H = 450,
};

enum OBSTACLE_XY
{
	OBSTACLE_X = 225,
	OBSTACLE_Y = MAIN_H - 80,
	OBSTACLE_W = MAIN_W - 100,
	OBSTACLE_H = 20,
};

enum GRAVITY_VALUE
{
	//GRAVITY_MAX = 200,
	GRAVITY_VALUE = 50,
};

enum SHAPE
{
	SHAPE_CIRCLE,
	SHAPE_BOX,

	SHAPE_MAX_SIZE = 50,
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	POINT m_Window_WH;
	HWND m_HWND;
	//HDC m_frontDC;
	HDC m_backDC;

	//장애물
	Box m_Obstacle_B; //큰 장애물

	//도형
	//Circle* m_circle;
	std::vector<Circle*> m_CircleList;
	//std::vector<Box> m_BoxList;
	//Box m_Box; //TODO::임시 반복적으로 생성되어야 한다.

	//도형 생성
	SHAPE m_CreateType;
	float m_CreateTime;

	GameManager();
	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	void RandCreateShaoe(float deltaTime);

	//충돌 체크
	bool CirclevsCircle(Circle* lhs, Circle* rhs);
	bool AABBvsCircle(Box* lhs, Circle* rhs);
public:
	~GameManager();

	static GameManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new GameManager;
		return m_pInstance;
	}

	void Init(HWND hWnd, HDC m_frontDC);
	void Update(float deltaTime);
	void Draw(HDC m_frontDC);
};