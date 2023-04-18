#pragma once
#include <list>
#include "BitMapManager.h"
#include "Meter.h"
//#include "framework.h"

#define SPEED_BACK 0.5
#define CLAP_BACK 0.05

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
	float m_ClapTime;
	//float m_Prev_MoveDistance;
	//Meter
	Meter m_Meter[SHOW_COUNT]; //�Ǿ��� ������� ��ĭ �ǳ� �� �ڿ� ����ϴ� ��
	//�ΰ��� �̹����� ����Ѵ�. �ι�° �̹����� ȭ�� ������ ������. ù��° �̹����� �ִ� x��ǥ�� �ι�° �̹����� ��ǥ�� �ǰ�. ������ ù��° �̹����� x ��ǥ�� ������ ��Ÿ�� �� ������ x��ǥ�� �ȴ�.
	//float m_MeterIMG_List[METER_SHOW_COUNT]; //meter ǥ�� ��� 
	//int m_Meter_Value[METER_SHOW_COUNT];

	//���
	void DrawGrass(HDC hdc);	//Ǯ
	//����+�ڳ���
	void DrawBack(HDC hdc);		
	//void DrawMeter(HDC hdc);	//����
	
	//��� �̵�
	void UpdateBack(float total_MoveDistance, float _Prev_MoveDistance); 

	//void UpdateMeter(float deltaTime, float thisTurn_MoveDistance);		//����

public:
	MapDraw();
	~MapDraw();

	//�ʱ� ����
	void InitialSet(SET setType);
	
	void DrawMap(HDC hdc);
	void UpdateMap(float total_MoveDistance, float _Prev_MoveDistance);
	//�¸��� �ڼ�ġ�� ���� ����
	void UpdateClapBack(float deltaTime);
	//���Ͱ� 0�� ���ö��� �Ǹ� Goal�� Ȱ��ȭ�Ѵ�.
	bool MeterEnd_GoalActiveCheck(); 


	float Get_mapXXXXXXXXXXXXXXXXXXX() {
		return m_BackIMG_X
			;
	}
};

