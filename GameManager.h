#pragma once

#include "BitMapManager.h"
#include "ObjectManager.h"
#include "MapDraw.h"
#include "UI.h"
#include "Character.h"

#define GMMgr GameManager::Get_Instance()
#define BitMapMgr BitMapManager::Get_Instance()

//���ָӴ� �Ծ��� �� ��� �ؽ�Ʈ ��
#define TEXT_SEC_1  1

enum SCENE
{
	SCENE_MENU,
	SCENE_GAME,
	SCENE_GAMECLEAR,
};


class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND;
	HDC m_frontDC;
	HDC m_backDC;

	POINT m_Widht_Height;
	SCENE m_Scene;
	//���� �� ��� : Score �ѹ��� ������Ű�� ���� ���
	std::vector<POINT> m_StarXY_List;
	HFONT m_Font[FONT_COUNT];


	MapDraw m_Map;
	UI m_UI;
	Character m_Character;
	ObjectManager m_ObjectMgr;
	float m_Prev_MoveDistance;

	//���ָӴ� ���� ��� üũ
	bool m_Draw_CashTextCheck;
	float m_DrawCashText_Time;

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
	void Update(float deltaTime); //��ǥ�̵��� ������ ��� return���� �Լ��� ������.
	void Draw();

	bool GameClearCheck();

	//GM�� ��� �̵� Ȯ�� + ĳ������ update �̵� Ȯ�ο��� 
	bool Get_GoalEndPositionCheck() { return m_ObjectMgr.Get_GoalEndPositionCheck(); } //���� Ư�� x ��ǥ�� ��°� üũ : ��� > ĳ���� �̵��� ���
	//Character���� ���
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_ObjectMgr.Set_GoalEndPositionCheck(_EndPositionCheck); }


	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	HFONT Get_Font(FONT fontType) { return m_Font[fontType]; };
	int Get_CharacterLife() { return m_Character.Get_CharacterLife(); }

	//BUMP_CHECK Get_CharacterBumpCheck() { m_Character.Get_Bump_Check(); }

	float Judgment_First_M_Value() //TravleDistance ������ M���� �Ÿ��� ������ ������ ���� value ���� �˾Ƴ���.
	{
		float tmp = m_Character.Get_Prev_TravelDistance() / METER_GAP * METER_VALUE_GAP;

		return METER_VALUE_START - tmp;
	}
};