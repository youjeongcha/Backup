#pragma once
#include"BitMap.h"
#include<stdio.h>


enum IMG
{
	//����ȭ��
	IMG_MENU_START,
	IMG_MENU_STAR_1 = IMG_MENU_START,	//��1
	IMG_MENU_STAR_2,					//��2
	IMG_MENU_STAR_3,					//��3
	IMG_MENU_TITLE,						//Ÿ��Ʋ
	IMG_MENU_SELECT_1,					//����1
	IMG_MENU_SELECT_2,					//����2
	IMG_MENU_SELECT_3,					//����3
	IMG_MENU_SELECT_4,					//����4
	IMG_MENU_SELECT_5,					//����5
	IMG_MENU_POINT,						//����Ʈ
	IMG_MENU_COUNT = IMG_MENU_POINT,

	//���
	IMG_BG_START,
	IMG_BG_GRASS = IMG_BG_START,		//�ܵ�
	IMG_BG_ELEPHANT,					//�ڳ���
	IMG_BG_SPECTATOR_1,					//����1
	IMG_BG_SPECTATOR_2,					//����2
	IMG_BG_SKY,							//�ϴ�
	IMG_BG_COUNT = IMG_BG_SKY,

	//Object
	IMG_OBJECT_START,
	IMG_OBJECT_CASH = IMG_OBJECT_START,		//��(���ָӴ�)
	IMG_OBJECT_GOAL,					//������
	IMG_OBJECT_COUNT = IMG_OBJECT_GOAL,

	//��ֹ�
	IMG_OBSTACLE_START,
	IMG_OBSTACLE_RING_LEFT_1 = IMG_OBSTACLE_START,	//�� ����1
	IMG_OBSTACLE_RING_RIGHT_1,						//�� ������1
	IMG_OBSTACLE_RING_LEFT_2,						//�� ����2
	IMG_OBSTACLE_RING_RIGHT_2,						//�� ������2
	IMG_OBSTACLE_POT_1,								//�׾Ƹ�1
	IMG_OBSTACLE_POT_2,								//�׾Ƹ�2
	IMG_OBSTACLE_COUNT = IMG_OBSTACLE_POT_2,

	//ĳ����
	IMG_CHARACTER_START,
	IMG_CHARACTER_FRONT_1 = IMG_CHARACTER_START,	//��1
	IMG_CHARACTER_FRONT_2,							//��2
	IMG_CHARACTER_JUMP,								//����
	IMG_CHARACTER_BUMP,								//�ε���
	IMG_CHARACTER_GOAL_1,							//�� ����1
	IMG_CHARACTER_GOAL_2,							//�� ����2
	IMG_CHARACTER_COUNT = IMG_CHARACTER_GOAL_2,

	//UI (���� + �Ÿ� + ���)
	IMG_UI_START,
	IMG_UI_SCORE_OUTLINE = IMG_UI_START,			//���� ǥ�� ��
	IMG_UI_LIFE,									//���
	IMG_UI_METER_OUTLINE,							//���� ǥ�� ��
	IMG_UI_COUNT = IMG_UI_METER_OUTLINE,



	//�̵� ���� �̹���
	IMG_MOVE = 14,


	//----------------------���-----------------------------
	PRINT_WH_MINUS = 18, //20, //�ʺ� ���� ����(�̹��� ũ�� ����)
	PRINT_XY_PLUS = PRINT_WH_MINUS / 2, //�̹��� ��� ��ǥ ����

	//�̹��� ������
	IMG_BG_SIZE = 60,
	IMG_SIZE = IMG_BG_SIZE - PRINT_WH_MINUS,
};

//�̱���
class BitMapManager
{
private:
	BitMap* m_parrBitMap; //BitMap�� �ϳ��� �־ �Ǳ⶧���� ��ü�� �������� �ʰ� *�� ����Ѵ�. �迭 ���.
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