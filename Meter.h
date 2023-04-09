#pragma once
#include "BitMapManager.h"
//#include <list>

//SHOW_FIRST �Լ��� �ݵ�� ���� ��µǴ� M�̰� 20������ ����Ǵ� ���� �ƴϹǷ� ū ���� ���
class Meter
{
private:
	float m_MeterIMG_X; //meter ǥ�� ��� 
	int m_Meter_Value;
	int m_Prev_Meter_Value; //������ ������ M�� value ��

public:
	Meter();
	~Meter();

	////�ʱ� ����
	//void InitialSet();

	//���� �����Ҷ� 
	void SetMeter(int _IMG_X, int _Meter_Value)
	{ 
		m_MeterIMG_X = _IMG_X;
		m_Meter_Value = _Meter_Value; 
	}

	void DrawMeter(HDC hdc);	//����
	void UpdateMeter(float total_MoveDistance, float _Prev_MoveDistance);		//����

	void Set_MeterIMG_X(float _IMG_X) { m_MeterIMG_X = _IMG_X; }
	void Set_MeterValue(int _Meter_Value) { m_Meter_Value = _Meter_Value; }
	int Get_Meter_Value() { return m_Meter_Value; }
	//���� value�� ��ֹ� �ε����� M�� ��������ֱ� ����
	int Get_Prev_Meter_Value() { return m_Prev_Meter_Value; }
};

