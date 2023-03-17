#pragma once

#include "BitMapManager.h"
#include "MapDraw.h"

#define BitMapMgr BitMapManager::Get_Instance()

class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND;
	//HDC m_hdc;
	HDC m_fDC;
	HDC m_bDC;
	RECT m_clientRect;
	MapDraw m_mDraw;

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

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
};

