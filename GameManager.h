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
	//��� ������ Ű�Է��� �־����� Ȯ��
	//bool KeyInputCheck();

	//���� 
	//GM�� ��� �̵� Ȯ�� + ĳ������ update �̵� Ȯ�ο��� 
	bool Get_GoalEndPositionCheck() { return ObjectMgr.Get_GoalEndPositionCheck(); } //���� Ư�� x ��ǥ�� ��°� üũ : ��� > ĳ���� �̵��� ���
	//Character���� ���
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { ObjectMgr.Set_GoalEndPositionCheck(_EndPositionCheck); }

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	HFONT Get_Font(FONT fontType) { return m_Font[fontType]; };
};

