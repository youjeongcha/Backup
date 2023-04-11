// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

enum WindowXY
{
	MAIN_X = 200,
	MAIN_Y = 100,
	MAIN_W = 900,
	MAIN_H = 450,
};


enum BUMP_RECT
{
	//BUMP_RECT_GAP = 5, 지정
	BUMP_RECT_GAP = 10,
};

enum BUMP_CHECK
{//현재 겹친 object의 속성에 따라 처리를 다르게 한다.(ex.골-게임 클리어, 장애물-목숨감소+게임오버)
	BUMP_GOAL,
	BUMP_OBSTACLE,
	BUMP_SCORE, //TODO::score는 변수로 별도로 관리를 한다.
	BUMP_CASH,
	BUMP_NONE,
};

enum SET //Init 함수의 switch문에 사용한다.
{
	SET_INIT,		//초기화
	SET_RESPAWN,	//리스폰 세팅
};

//enum SPEEDMETER
//{
//	SPEED_METER = 20,
//};



//-------------------------------IMG-----------------------------------
enum MAP_IMG
{
	//잔디
	IMG_GRASS_X = 0,
	IMG_GRASS_Y = (int)(MAIN_H / 2.6), //(int)(MAIN_H / 2.9f),
	IMG_GRASS_W = MAIN_W,// + MAIN_X,
	IMG_GRASS_H = (int)(MAIN_H / 2.2f) - 15,

	//관중(7) 
	IMG_SPECTATOR_W = 65,
	//IMG_SPECTATOR_H = 64,
	//IMG_SPECTATOR_Y = IMG_GRASS_Y - IMG_SPECTATOR_H,

	//코끼리
	IMG_ELEPHANT_W = 66,
	IMG_ELEPHANT_H = 67,
	IMG_ELEPHANT_Y = IMG_GRASS_Y - IMG_ELEPHANT_H,
};

//캐릭터
enum IMG_CHARACTER
{
	//IMG_CHARACTER_Y = MAIN_H - 150,
	IMG_CHARACTER_W = 60,
	IMG_CHARACTER_H = IMG_CHARACTER_W + 10,
	IMG_CHARACTER_X = 80,
	IMG_CHARACTER_Y = IMG_GRASS_Y + IMG_GRASS_H - IMG_CHARACTER_H - 5,


	IMG_CHARACTER_COLLIDER_W = IMG_CHARACTER_W - BUMP_RECT_GAP * 2,
	IMG_CHARACTER_COLLIDER_H = IMG_CHARACTER_H - BUMP_RECT_GAP * 2,
};

//M 이미지의 XYWH
enum METER_IMG
{
	//METER_GAP = IMG_SPECTATOR_W * 8,
	METER_GAP = 500,
	METER_X = IMG_CHARACTER_X,
	//METER_SECOND_X = IMG_CHARACTER_X + METER_GAP,
	METER_Y = IMG_GRASS_Y + IMG_GRASS_H,
	METER_W = 80,
	METER_H = 30,
	METER_ACROSS_ONE = METER_GAP * 2,


	////첫째 M 표시의 제한 범위
	//METER_START_SHOW_X = -METER_W,
	//METER_END_SHOW_X = MAIN_W,

	//METER_SHOW_FISRT = 0,
	//METER_SHOW_SECOND,
	//METER_SHOW_COUNT,
};

//거리기준
enum METER_RATIO
{
	METER_RATIO_100 = METER_X,
	METER_RATIO_90 = METER_RATIO_100 + METER_GAP,
	METER_RATIO_80 = METER_RATIO_90 + METER_GAP,
	METER_RATIO_70 = METER_RATIO_80 + METER_GAP,
	METER_RATIO_60 = METER_RATIO_70 + METER_GAP,
	METER_RATIO_50 = METER_RATIO_60 + METER_GAP,
	METER_RATIO_40 = METER_RATIO_50 + METER_GAP,
	METER_RATIO_30 = METER_RATIO_40 + METER_GAP,
	METER_RATIO_20 = METER_RATIO_30 + METER_GAP,
	METER_RATIO_10 = METER_RATIO_20 + METER_GAP,
	METER_RATIO_0 = METER_RATIO_10 + METER_GAP,
};

enum SHOW_IMG
{
	//시작점과 끝점 이미지 표시 제한 범위
	START_SHOW_X = -METER_W,
	END_SHOW_X = MAIN_W,

	SHOW_FISRT = 0,
	SHOW_SECOND,
	SHOW_COUNT,
};

enum GOAL
{
	GOAL_IMG_W = 60,
	GOAL_IMG_H = 50,

	GOAL_IMG_X = END_SHOW_X,
	GOAL_IMG_Y = IMG_CHARACTER_Y + 20,
	//GOAL_IMG_R = GOAL_IMG_L + GOAL_IMG_W,
	//GOAL_IMG_B = GOAL_IMG_T + GOAL_IMG_H,


	//GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

//Goal 이동가능
enum GOAL_IMG_ARRIVE
{
	GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

enum FIRJAR_IMG
{
	FIRJAR_X = METER_RATIO_80 - 50,
	FIRJAR_Y = IMG_CHARACTER_Y + 25,

	FIRJAR_W = 45,
	FIRJAR_H = 50,

	FIRJAR_COLLIDER_W = FIRJAR_W - BUMP_RECT_GAP * 2,
	FIRJAR_COLLIDER_H = FIRJAR_H - BUMP_RECT_GAP * 2,
};

enum FIRRING_IMG
{
	FIRRING_X = METER_RATIO_80 + 200,
	FIRRING_Y = IMG_ELEPHANT_Y + IMG_ELEPHANT_H,

	FIRRING_W = 25,
	FIRRING_H = IMG_CHARACTER_H * 2,

	//Collider rect 세팅용
	FIRRING_COLLIDER_W = 5,
	FIRRING_COLLIDER_H = 5,

	//작은 링 H
	//FIRRING_S_H = IMG_CHARACTER_H * 2 - 30,
	FIRRING_S_H = IMG_CHARACTER_H * 2 - 30,

	//Collider rect 세팅용
	FIRRING_COLLIDER_SAMLL_GAP = 1,

	//---------------복주머니---------------
	FIRRING_CASH_X_GAP = 13,
	FIRRING_CASH_Y_GAP = 20,

	//복주머니 크기
	FIRRING_CASH_W = 22,
	FIRRING_CASH_H = FIRRING_CASH_W + 5,
};

//---------------------캐릭터-----------------------

enum CHARACTER_JUMP
{
	CHARACTER_JUMP_NONE,
	CHARACTER_JUMP_UP,
	CHARACTER_JUMP_DOWN,

	///CHARACTER_JUMP_GAP = 10,
	CHARACTER_JUMP_GAP = 300,

	CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 100, //가장 높은 위치
	//CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 120, //가장 높은 위치
	CHARACTER_JUMP_MIN_Y = IMG_CHARACTER_Y, //가장 낮은 위치 == 처음의 Y
};



//----------------------------------------------------

//미터 수치 글자
enum METER_VALUE
{
	//METER_VALUE_X_GAP = 27, //이미지 시작 x와의 갭을 의미
	METER_VALUE_X_GAP = METER_W - 30, //이미지 시작 좌표인 m_MeterIMG_X에 더해준다.
	METER_VALUE_Y = METER_Y + 6,

	METER_VALUE_START = 100,
	METER_VALUE_END = 0,
	//METER_VALUE_END = 80,
	METER_VALUE_GAP = 10,
	METER_VALUE_ACROSS_ONE = METER_VALUE_GAP * 2,
};

//-------------------------------거리-----------------------------------
enum TRAVELDISTANCE //사실상 배경이 움직이는 범위값이라고 보아도 무방하다
{
	TRAVELDISTANCE_START = 0,
	//골이 나타나고 배경 움직임 > 캐릭터 움직임으로 전환되는 시점
	TRAVELDISTANCE_END = METER_GAP * 11 - 120,
	//TRAVELDISTANCE_END = 440,
	//TRAVELDISTANCE_END = 420,

	//TRAVELDISTANCE_MOVE_PER_SEC = 10, //초당 움직이는 거리
	TRAVELDISTANCE_MOVE_PER_SEC = 200, //초당 움직이는 거리
};