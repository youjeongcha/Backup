#pragma once
#include <list>
#include <time.h>
#include "framework.h"
#include "Circle.h"
#include "Box.h"

#define GMMgr GameManager::Get_Instance()

enum GRAVITY_VALUE
{
	//GRAVITY_MAX = 200,
	GRAVITY_VALUE = 50,
};

enum SHAPE
{
	SHAPE_CIRCLE,
	SHAPE_BOX,
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	POINT m_Window_WH;
	HWND m_HWND;
	//HDC m_frontDC;
	HDC m_backDC;

	//도형
	Circle* m_circle;
	std::list<Circle*> m_CircleList;
	std::list<Box> m_BoxList;
	Box m_Box; //TODO::임시 반복적으로 생성되어야 한다.

	//도형 생성
	SHAPE m_CreateType;
	float m_CreateTime;

	GameManager();
	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	void RandCreateShaoe(float deltaTime);
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