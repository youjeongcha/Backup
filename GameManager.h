#pragma once

#include "BitMapManager.h"
#include "ObjectManager.h"
#include "MapDraw.h"
#include "UI.h"
#include "Character.h"

#define GMMgr GameManager::Get_Instance()
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
	HDC m_frontDC;
	HDC m_backDC;
	POINT m_Widht_Height;
	SCENE m_scene;
	std::vector<POINT> m_StarXY_List;
	HFONT m_Font[FONT_COUNT];


	MapDraw m_Draw;
	UI m_UI;
	Character character;
	ObjectManager ObjectMgr;


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
	//사용 가능한 키입력이 있었는지 확인
	//bool KeyInputCheck();

	//질문 
	//GM의 배경 이동 확인 + 캐릭터의 update 이동 확인에서 
	bool Get_GoalEndPositionCheck() { return ObjectMgr.Get_GoalEndPositionCheck(); } //골이 특정 x 좌표에 닿는것 체크 : 배경 > 캐릭터 이동을 담당
	//Character에서 사용
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { ObjectMgr.Set_GoalEndPositionCheck(_EndPositionCheck); }

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	HFONT Get_Font(FONT fontType) { return m_Font[fontType]; };
};

