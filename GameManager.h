#pragma once

#include "BitMapManager.h"
#include "ObjectManager.h"
#include "MapDraw.h"
#include "UI.h"
#include "Character.h"

#define GMMgr GameManager::Get_Instance()
#define BitMapMgr BitMapManager::Get_Instance()

//복주머니 먹었을 때 드는 텍스트 초
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
	//이전 씬 기록 : Score 한번만 증가시키기 위해 사용
	std::vector<POINT> m_StarXY_List;
	HFONT m_Font[FONT_COUNT];


	MapDraw m_Map;
	UI m_UI;
	Character m_Character;
	ObjectManager m_ObjectMgr;
	float m_Prev_MoveDistance;

	//복주머니 점수 출력 체크
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
	void Update(float deltaTime); //좌표이동이 금지될 경우 return으로 함수를 끝낸다.
	void Draw();

	bool GameClearCheck();

	//GM의 배경 이동 확인 + 캐릭터의 update 이동 확인에서 
	bool Get_GoalEndPositionCheck() { return m_ObjectMgr.Get_GoalEndPositionCheck(); } //골이 특정 x 좌표에 닿는것 체크 : 배경 > 캐릭터 이동을 담당
	//Character에서 사용
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_ObjectMgr.Set_GoalEndPositionCheck(_EndPositionCheck); }


	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);
	HFONT Get_Font(FONT fontType) { return m_Font[fontType]; };
	int Get_CharacterLife() { return m_Character.Get_CharacterLife(); }

	//BUMP_CHECK Get_CharacterBumpCheck() { m_Character.Get_Bump_Check(); }

	float Judgment_First_M_Value() //TravleDistance 값으로 M간의 거리를 나누어 비율을 구해 value 값을 알아낸다.
	{
		float tmp = m_Character.Get_Prev_TravelDistance() / METER_GAP * METER_VALUE_GAP;

		return METER_VALUE_START - tmp;
	}
};