#pragma once
#include"BitMap.h"
#include<stdio.h>


enum IMG
{
	//시작화면
	IMG_MENU_START,
	IMG_MENU_STAR_1 = IMG_MENU_START,	//별1
	IMG_MENU_STAR_2,					//별2
	IMG_MENU_STAR_3,					//별3
	IMG_MENU_TITLE,						//타이틀
	IMG_MENU_SELECT_1,					//선택1
	IMG_MENU_SELECT_2,					//선택2
	IMG_MENU_SELECT_3,					//선택3
	IMG_MENU_SELECT_4,					//선택4
	IMG_MENU_SELECT_5,					//선택5
	IMG_MENU_POINT,						//포인트
	IMG_MENU_COUNT = IMG_MENU_POINT,

	//배경
	IMG_BG_START,
	IMG_BG_GRASS = IMG_BG_START,		//잔디
	IMG_BG_ELEPHANT,					//코끼리
	IMG_BG_SPECTATOR_1,					//관중1
	IMG_BG_SPECTATOR_2,					//관중2
	IMG_BG_SKY,							//하늘
	IMG_BG_COUNT = IMG_BG_SKY,

	//Object
	IMG_OBJECT_START,
	IMG_OBJECT_CASH = IMG_OBJECT_START,		//돈(복주머니)
	IMG_OBJECT_GOAL,					//도착점
	IMG_OBJECT_COUNT = IMG_OBJECT_GOAL,

	//장애물
	IMG_OBSTACLE_START,
	IMG_OBSTACLE_RING_LEFT_1 = IMG_OBSTACLE_START,	//링 왼쪽1
	IMG_OBSTACLE_RING_RIGHT_1,						//링 오른쪽1
	IMG_OBSTACLE_RING_LEFT_2,						//링 왼쪽2
	IMG_OBSTACLE_RING_RIGHT_2,						//링 오른쪽2
	IMG_OBSTACLE_POT_1,								//항아리1
	IMG_OBSTACLE_POT_2,								//항아리2
	IMG_OBSTACLE_COUNT = IMG_OBSTACLE_POT_2,

	//캐릭터
	IMG_CHARACTER_START,
	IMG_CHARACTER_FRONT_1 = IMG_CHARACTER_START,	//앞1
	IMG_CHARACTER_FRONT_2,							//앞2
	IMG_CHARACTER_JUMP,								//점프
	IMG_CHARACTER_BUMP,								//부딪힘
	IMG_CHARACTER_GOAL_1,							//골에 도착1
	IMG_CHARACTER_GOAL_2,							//골에 도착2
	IMG_CHARACTER_COUNT = IMG_CHARACTER_GOAL_2,

	//UI (점수 + 거리 + 목숨)
	IMG_UI_START,
	IMG_UI_SCORE_OUTLINE = IMG_UI_START,			//점수 표시 선
	IMG_UI_LIFE,									//목숨
	IMG_UI_METER_OUTLINE,							//미터 표시 선
	IMG_UI_COUNT = IMG_UI_METER_OUTLINE,



	//이동 가능 이미지
	IMG_MOVE = 14,


	//----------------------출력-----------------------------
	PRINT_WH_MINUS = 18, //20, //너비 높이 감소(이미지 크기 조절)
	PRINT_XY_PLUS = PRINT_WH_MINUS / 2, //이미지 출력 좌표 조절

	//이미지 사이즈
	IMG_BG_SIZE = 60,
	IMG_SIZE = IMG_BG_SIZE - PRINT_WH_MINUS,
};

//싱글톤
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap은 하나만 있어도 되기때문에 객체를 생성하지 않고 *로 사용한다. 배열 사용.
	static BitMapManager* m_hThis;
	BitMapManager();

public:
	static BitMapManager* GetInstance()
	{
		if (NULL == m_hThis)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	~BitMapManager();

	BitMap* GetImage(IMG index) { return &m_parrBitMap[index]; }

	void Init(HWND hWnd);
};