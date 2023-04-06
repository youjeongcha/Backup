#pragma once
#include "BitMapManager.h"
//#include <list>


class Meter
{
private:
	float m_MeterIMG_X; //meter 표시 출력 
	int m_Meter_Value;
	//float m_Prev_MoveDistance;

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
};

