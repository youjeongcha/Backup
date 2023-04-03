#pragma once
#include<stdio.h>
#include <string>
#include"BitMap.h"

enum IMG
{
	//----------시작화면----------
	
	//타이틀
	IMG_MENU_TITLE_START,
	IMG_MENU_TITLE_1 = IMG_MENU_TITLE_START,		//타이틀
	IMG_MENU_TITLE_2,								//별1
	IMG_MENU_TITLE_3,								//별2
	IMG_MENU_TITLE_4,								//별3
	IMG_MENU_TITLE_COUNT = IMG_MENU_TITLE_4 - IMG_MENU_TITLE_START + 1,

	//메뉴
	IMG_MENU_SELECT_START = IMG_MENU_TITLE_4 + 1,
	IMG_MENU_SELECT_1 = IMG_MENU_SELECT_START,		//선택1
	IMG_MENU_SELECT_2,								//선택2
	IMG_MENU_SELECT_3,								//선택3
	IMG_MENU_SELECT_4,								//선택4
	IMG_MENU_SELECT_5,								//선택5
	//IMG_MENU_SELECT_6,								//선택 검은 배경으로 //선택지 깜빡거림을 구현하기 위해 추가한 리소스
	IMG_MENU_SELECT_COUNT = IMG_MENU_SELECT_5 - IMG_MENU_SELECT_START + 1,

	//포인트
	IMG_MENU_POINT_START = IMG_MENU_SELECT_5 + 1,
	IMG_MENU_POINT = IMG_MENU_POINT_START,			//포인트
	IMG_MENU_POINT_COUNT = IMG_MENU_POINT - IMG_MENU_POINT_START + 1,

	//배경
	IMG_BG_START = IMG_MENU_POINT + 1,
	IMG_BG_GRASS = IMG_BG_START,					//잔디
	IMG_BG_ELEPHANT,								//코끼리
	IMG_BG_SPECTATOR_1,								//관중1
	IMG_BG_SPECTATOR_2,								//관중2
	IMG_BG_COUNT = IMG_BG_SPECTATOR_2 - IMG_BG_START + 1,

	//돈(복주머니)
	IMG_OBJECT_CASH_START = IMG_BG_SPECTATOR_2 + 1,
	IMG_OBJECT_CASH = IMG_OBJECT_CASH_START,				//돈(복주머니)
	IMG_OBJECT_CASH_COUNT = IMG_OBJECT_CASH - IMG_OBJECT_CASH_START + 1,

	//도착점
	IMG_OBJECT_GOAL_START = IMG_OBJECT_CASH + 1,
	IMG_OBJECT_GOAL = IMG_OBJECT_GOAL_START,				//도착점
	IMG_OBJECT_GOAL_COUNT = IMG_OBJECT_GOAL - IMG_OBJECT_GOAL_START + 1,

	//항아리
	IMG_OBJECT_POT_START = IMG_OBJECT_GOAL + 1,
	IMG_OBJECT_POT_1 = IMG_OBJECT_POT_START,				//항아리1
	IMG_OBJECT_POT_2,										//항아리2
	IMG_OBJECT_POT_COUNT = IMG_OBJECT_POT_2 - IMG_OBJECT_POT_START + 1,

	//링
	IMG_OBJECT_RING_START = IMG_OBJECT_POT_2 + 1,
	IMG_OBJECT_RING_LEFT_1 = IMG_OBJECT_RING_START,				//링 왼쪽1
	IMG_OBJECT_RING_RIGHT_1,								//링 오른쪽1
	IMG_OBJECT_RING_LEFT_2,									//링 왼쪽2
	IMG_OBJECT_RING_RIGHT_2,								//링 오른쪽2
	IMG_OBJECT_RING_COUNT = IMG_OBJECT_RING_RIGHT_2 - IMG_OBJECT_RING_START + 1,

	//캐릭터
	IMG_CHARACTER_START = IMG_OBJECT_RING_RIGHT_2 + 1,
	IMG_CHARACTER_FRONT_1 = IMG_CHARACTER_START,			//앞1
	IMG_CHARACTER_FRONT_2,									//앞2
	IMG_CHARACTER_FRONT_3,									//앞3	//점프
	IMG_CHARACTER_GOAL_1,									//골에 도착1
	IMG_CHARACTER_GOAL_2,									//골에 도착2
	IMG_CHARACTER_BUMP,										//부딪힘
	IMG_CHARACTER_COUNT = IMG_CHARACTER_GOAL_2 - IMG_CHARACTER_START + 1,

	//인터페이스 (점수 + 거리 + 목숨)
	IMG_INTERFACE_START = IMG_CHARACTER_GOAL_2 + 1,
	IMG_INTERFACE_SCORE_OUTLINE = IMG_INTERFACE_START,		//점수 표시 선
	IMG_INTERFACE_LIFE,										//목숨
	IMG_INTERFACE_METER_OUTLINE,							//미터 표시 선
	IMG_INTERFACE_COUNT = IMG_INTERFACE_METER_OUTLINE - IMG_INTERFACE_START + 1,

	//IMG의 총 개수
	IMG_COUNT = IMG_INTERFACE_METER_OUTLINE
};









//싱글톤
class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap* m_parrBitMap; //BitMap은 하나만 있어도 되기때문에 객체를 생성하지 않고 *로 사용한다. 배열 사용.

	BitMapManager();

public:
	static BitMapManager* Get_Instance()
	{
		if (NULL == m_hThis)
			m_hThis = new BitMapManager;
		return m_hThis;
	}

	~BitMapManager();

	BitMap* GetImage(IMG index) { return &m_parrBitMap[index]; }

	void Init(HWND hWnd);
};