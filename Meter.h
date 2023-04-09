#pragma once
#include "BitMapManager.h"
//#include <list>

//SHOW_FIRST 함수가 반드시 먼저 출력되는 M이고 20단위로 변경되는 것이 아니므로 큰 수를 계산
class Meter
{
private:
	float m_MeterIMG_X; //meter 표시 출력 
	int m_Meter_Value;
	int m_Prev_Meter_Value; //지나온 직전의 M의 value 값

public:
	Meter();
	~Meter();

	////초기 세팅
	//void InitialSet();

	//게임 시작할때 
	void SetMeter(int _IMG_X, int _Meter_Value)
	{ 
		m_MeterIMG_X = _IMG_X;
		m_Meter_Value = _Meter_Value; 
	}

	void DrawMeter(HDC hdc);	//미터
	void UpdateMeter(float total_MoveDistance, float _Prev_MoveDistance);		//미터

	void Set_MeterIMG_X(float _IMG_X) { m_MeterIMG_X = _IMG_X; }
	void Set_MeterValue(int _Meter_Value) { m_Meter_Value = _Meter_Value; }
	int Get_Meter_Value() { return m_Meter_Value; }
	//이전 value를 장애물 부딪히고 M에 적용시켜주기 위해
	int Get_Prev_Meter_Value() { return m_Prev_Meter_Value; }
};

