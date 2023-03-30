#pragma once
#include<stdio.h>
#include <string>
#include"BitMap.h"

enum IMG
{
	//----------����ȭ��----------
	
	//Ÿ��Ʋ
	IMG_MENU_TITLE_START,
	IMG_MENU_TITLE_1 = IMG_MENU_TITLE_START,		//Ÿ��Ʋ
	IMG_MENU_TITLE_2,								//��1
	IMG_MENU_TITLE_3,								//��2
	IMG_MENU_TITLE_4,								//��3
	IMG_MENU_TITLE_COUNT = IMG_MENU_TITLE_4 - IMG_MENU_TITLE_START + 1,

	//�޴�
	IMG_MENU_SELECT_START = IMG_MENU_TITLE_4 + 1,
	IMG_MENU_SELECT_1 = IMG_MENU_SELECT_START,		//����1
	IMG_MENU_SELECT_2,								//����2
	IMG_MENU_SELECT_3,								//����3
	IMG_MENU_SELECT_4,								//����4
	IMG_MENU_SELECT_5,								//����5
	//IMG_MENU_SELECT_6,								//���� ���� ������� //������ �����Ÿ��� �����ϱ� ���� �߰��� ���ҽ�
	IMG_MENU_SELECT_COUNT = IMG_MENU_SELECT_5 - IMG_MENU_SELECT_START + 1,

	//����Ʈ
	IMG_MENU_POINT_START = IMG_MENU_SELECT_5 + 1,
	IMG_MENU_POINT = IMG_MENU_POINT_START,			//����Ʈ
	IMG_MENU_POINT_COUNT = IMG_MENU_POINT - IMG_MENU_POINT_START + 1,

	//���
	IMG_BG_START = IMG_MENU_POINT + 1,
	IMG_BG_GRASS = IMG_BG_START,					//�ܵ�
	IMG_BG_ELEPHANT,								//�ڳ���
	IMG_BG_SPECTATOR_1,								//����1
	IMG_BG_SPECTATOR_2,								//����2
	IMG_BG_COUNT = IMG_BG_SPECTATOR_2 - IMG_BG_START + 1,

	//��(���ָӴ�)
	IMG_OBJECT_CASH_START = IMG_BG_SPECTATOR_2 + 1,
	IMG_OBJECT_CASH = IMG_OBJECT_CASH_START,				//��(���ָӴ�)
	IMG_OBJECT_CASH_COUNT = IMG_OBJECT_CASH - IMG_OBJECT_CASH_START + 1,

	//������
	IMG_OBJECT_GOAL_START = IMG_OBJECT_CASH + 1,
	IMG_OBJECT_GOAL = IMG_OBJECT_GOAL_START,				//������
	IMG_OBJECT_GOAL_COUNT = IMG_OBJECT_GOAL - IMG_OBJECT_GOAL_START + 1,

	//�׾Ƹ�
	IMG_OBJECT_POT_START = IMG_OBJECT_GOAL + 1,
	IMG_OBJECT_POT_1 = IMG_OBJECT_POT_START,				//�׾Ƹ�1
	IMG_OBJECT_POT_2,										//�׾Ƹ�2
	IMG_OBJECT_POT_COUNT = IMG_OBJECT_POT_2 - IMG_OBJECT_POT_START + 1,

	//��
	IMG_OBJECT_RING_START = IMG_OBJECT_POT_2 + 1,
	IMG_OBJECT_RING_LEFT_1 = IMG_OBJECT_RING_START,				//�� ����1
	IMG_OBJECT_RING_RIGHT_1,								//�� ������1
	IMG_OBJECT_RING_LEFT_2,									//�� ����2
	IMG_OBJECT_RING_RIGHT_2,								//�� ������2
	IMG_OBJECT_RING_COUNT = IMG_OBJECT_RING_RIGHT_2 - IMG_OBJECT_RING_START + 1,

	//ĳ����
	IMG_CHARACTER_START = IMG_OBJECT_RING_RIGHT_2 + 1,
	IMG_CHARACTER_FRONT_1 = IMG_CHARACTER_START,			//��1
	IMG_CHARACTER_FRONT_2,									//��2
	IMG_CHARACTER_FRONT_3,									//��3	//����
	IMG_CHARACTER_GOAL_1,									//�� ����1
	IMG_CHARACTER_GOAL_2,									//�� ����2
	IMG_CHARACTER_BUMP,										//�ε���
	IMG_CHARACTER_COUNT = IMG_CHARACTER_GOAL_2 - IMG_CHARACTER_START + 1,

	//�������̽� (���� + �Ÿ� + ���)
	IMG_INTERFACE_START = IMG_CHARACTER_GOAL_2 + 1,
	IMG_INTERFACE_SCORE_OUTLINE = IMG_INTERFACE_START,		//���� ǥ�� ��
	IMG_INTERFACE_LIFE,										//���
	IMG_INTERFACE_METER_OUTLINE,							//���� ǥ�� ��
	IMG_INTERFACE_COUNT = IMG_INTERFACE_METER_OUTLINE - IMG_INTERFACE_START + 1,

	//IMG�� �� ����
	IMG_COUNT = IMG_INTERFACE_METER_OUTLINE
};

enum MAP_IMG_XYWH
{
	//�ܵ�
	IMG_GRASS_X = 0,
	IMG_GRASS_Y = (int)(MAIN_H / 2.6), //(int)(MAIN_H / 2.9f),
	IMG_GRASS_W = MAIN_W,// + MAIN_X,
	IMG_GRASS_H = (int)(MAIN_H / 2.2f),

	//����(7) 
	IMG_SPECTATOR_W = 65,
	//IMG_SPECTATOR_H = 64,
	//IMG_SPECTATOR_Y = IMG_GRASS_Y - IMG_SPECTATOR_H,

	//�ڳ���
	IMG_ELEPHANT_W = 66,
	IMG_ELEPHANT_H = 67,
	IMG_ELEPHANT_Y = IMG_GRASS_Y - IMG_ELEPHANT_H,
};

//ĳ����
enum IMG_CHARACTER
{
	//Ÿ��Ʋ
	IMG_CHARACTER_X = 80,
	IMG_CHARACTER_Y = MAIN_H - 150,
	IMG_CHARACTER_W = 60,
	IMG_CHARACTER_H = IMG_CHARACTER_W + 10,
};

//Goal �̵�����
enum GOAL_MOVE
{
	GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

//M �̹����� XYWH
enum METER_IMG
{
	METER_GAP = IMG_SPECTATOR_W * 8,
	METER_X = IMG_CHARACTER_X,
	METER_SECOND_X = IMG_CHARACTER_X + METER_GAP,
	METER_Y = IMG_GRASS_Y + IMG_GRASS_H,
	METER_W = 80,
	METER_H = 30,
	METER_ACROSS_ONE = METER_GAP * 2,


	//ù° M ǥ���� ���� ����
	METER_START_SHOW_X = -METER_W,
	METER_END_SHOW_X = MAIN_W,

	METER_SHOW_FISRT = 0,
	METER_SHOW_SECOND,
	METER_SHOW_COUNT,
};

//���� ��ġ ����
enum METER_VALUE
{
	//METER_VALUE_X_GAP = 27, //�̹��� ���� x���� ���� �ǹ�
	METER_VALUE_X_GAP = METER_W - 30, //�̹��� ���� ��ǥ�� m_MeterIMG_X�� �����ش�.
	METER_VALUE_Y = METER_Y + 6,

	METER_VALUE_START = 100,
	METER_VALUE_END = 0,
	//METER_VALUE_END = 80,
	METER_VALUE_GAP = 10,
	METER_VALUE_ACROSS_ONE = METER_VALUE_GAP * 2,
};

//-----------�Ÿ�-------------
enum TRAVELDISTANCE //��ǻ� ����� �����̴� �������̶�� ���Ƶ� �����ϴ�
{
	TRAVELDISTANCE_START = 0,
	//���� ��Ÿ���� ��� ������ > ĳ���� ���������� ��ȯ�Ǵ� ����
	//TRAVELDISTANCE_END = 1300, 
	//TRAVELDISTANCE_END = 1000, 
	TRAVELDISTANCE_END = METER_GAP * 11 - 120, 

	TRAVELDISTANCE_MOVE_PER_SEC = 10, //�ʴ� �����̴� �Ÿ�
};



//�̱���
class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap* m_parrBitMap; //BitMap�� �ϳ��� �־ �Ǳ⶧���� ��ü�� �������� �ʰ� *�� ����Ѵ�. �迭 ���.

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