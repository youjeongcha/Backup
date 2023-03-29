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
	//����(7)-�ڳ���(1)-����(7)-�ڳ���(1)
	IMG_BACK_COUNT = 16,

	//����(7)
	//IMG_SPECTATOR_COUNT = 15,

	//�ڳ���(1)
	IMG_ELEPHANT_FIRST = 7,
	IMG_ELEPHANT_SECOND = 15,
};


class MapDraw
{
private:
	std::list<IMG> m_BackIMG_List;
	float m_BackIMG_X;
	//Meter
	Meter m_Meter[METER_SHOW_COUNT]; //�Ǿ��� ������� ��ĭ �ǳ� �� �ڿ� ����ϴ� ��
	//�ΰ��� �̹����� ����Ѵ�. �ι�° �̹����� ȭ�� ������ ������. ù��° �̹����� �ִ� x��ǥ�� �ι�° �̹����� ��ǥ�� �ǰ�. ������ ù��° �̹����� x ��ǥ�� ������ ��Ÿ�� �� ������ x��ǥ�� �ȴ�.
	//float m_MeterIMG_List[METER_SHOW_COUNT]; //meter ǥ�� ��� 
	//int m_Meter_Value[METER_SHOW_COUNT];

	//���
	void DrawGrass(HDC hdc);	//Ǯ
	void DrawBack(HDC hdc);		//����+�ڳ���
	//void DrawMeter(HDC hdc);	//����

	void UpdateBack(float deltaTime, float thisTurn_MoveDistance); //���
	//void UpdateMeter(float deltaTime, float thisTurn_MoveDistance);		//����

public:
	MapDraw();
	~MapDraw();
	
	void DrawMap(HDC hdc);
	void UpdateMap(float deltaTime, float thisTurn_MoveDistance);
};

