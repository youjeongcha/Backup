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