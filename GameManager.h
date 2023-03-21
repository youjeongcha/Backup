#pragma once

#include "BitMapManager.h"
#include "MapDraw.h"
#include "UI.h"

#define BitMapMgr BitMapManager::Get_Instance()

enum SCENE
{
	SCENE_MENU,
	SCENE_GAME,
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND;
	HDC m_fDC;
	HDC m_bDC;
	RECT m_clientRect;
	SCENE m_scene;

	MapDraw m_Draw;
	UI m_UI;


	GameManager();

public:
	~GameManager();

	static GameManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new GameManager;
		return m_pInstance;
	}

	void init(HWND hWnd);
	void Update(float deltaTime);
	void Draw();
	//void KeyState(); //≈∞ ¡∂¿€

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
};

