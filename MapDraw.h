#pragma once
#include "BitMapManager.h"
#include "Meter.h"
#include <list>

enum SPEEDBACK
{
	SPEED_BACK = 10,
	//SPEED_BACK = 180,
};

enum IMG_BACK
{
	//관중(7)-코끼리(1)-관중(7)-코끼리(1)
	IMG_BACK_COUNT = 16,

	//관중(7)
	//IMG_SPECTATOR_COUNT = 15,

	//코끼리(1)
	IMG_ELEPHANT_FIRST = 7,
	IMG_ELEPHANT_SECOND = 15,
};


class MapDraw
{
private:
	std::list<IMG> m_BackIMG_List;
	float m_BackIMG_X;
	//Meter
	Meter m_Meter[METER_SHOW_COUNT]; //맨앞이 사라지고 한칸 건너 맨 뒤에 출력하는 식
	//두개의 이미지를 사용한다. 두번째 이미지가 화면 밖으로 나가면. 첫번째 이미지가 있던 x좌표가 두번째 이미지의 좌표가 되고. 기존의 첫번째 이미지의 x 좌표는 앞으로 나타날 빈 공간의 x좌표가 된다.
	//float m_MeterIMG_List[METER_SHOW_COUNT]; //meter 표시 출력 
	//int m_Meter_Value[METER_SHOW_COUNT];

	//배경
	void DrawGrass(HDC hdc);	//풀
	void DrawBack(HDC hdc);		//관중+코끼리
	//void DrawMeter(HDC hdc);	//미터

	void UpdateBack(float deltaTime, float thisTurn_MoveDistance); //배경
	//void UpdateMeter(float deltaTime, float thisTurn_MoveDistance);		//미터

public:
	MapDraw();
	~MapDraw();
	
	void DrawMap(HDC hdc);
	void UpdateMap(float deltaTime, float thisTurn_MoveDistance);
};

