#pragma once
#include "BitMapManager.h"
#include "Card.h"
#include <time.h>
#include <vector>
#include <cmath>
#include <queue>

enum CARD_XY
{
	CARD_FIRST_X = 50,
	CARD_FIRST_Y = 200,

	CARD_NEXT_X = 150,
	CARD_NEXT_Y = 100,
};

enum SHOW
{
	//ī�� �ʱ�ȭ(�̹��� �ֱ�)CardInit, ����CardShuffleMix, ī�� �����ֱ� �� ������ + �ո� ���� ������ ���CardTurn_All.
	SHOW_CARD_RANGE = IMAGE_COUNT * 2,
	//�� ��� ���� �̹���
	SHOW_CHANGE_CARD_RANGE = SHOW_CARD_RANGE + IMAGE_CHANGE_TIGER,

	SHOW_ONELINE = 5, //���ٿ� ������ ī�� ��
};

enum SEQUENCE
{
	SEQUENCE_MENU,
	SEQUENCE_STROY,
	SEQUENCE_RABBIT,
	SEQUENCE_SHOWCARD, //ī�� ���� �����ֱ�
	SEQUENCE_CARD_ORDERTURN, //�� ���� ��ü ī�� ���������� ��
	SEQUENCE_CARDGAME,
	SEQUENCE_GAMEOVER,
	SEQUENCE_CLEAR,
};

enum INIT
{
	INIT_FIRST,
	INIT_RE,
};

enum FRONTCHECK
{
	FRONT_ID1 = 0,
	FRONT_ID2 = 1,

	FRONT_COUNT_2 = 2,
};

enum TIMER
{
	TIMER_ID_SCENE,
	TIMER_ID_CARD_ORDER, //ī�� ���� ������� ��������
	TIMER_ID_CARD_ALL, //ī�� 2�� �ѹ��� ��������

	TIMER_SCENE_SEC = 1000,
	TIMER_CARD_ODER_SEC = 1000, //ī�� ���� �������� �ϳ��� ������ �ð�
	TIMER_CARD_ALL_SEC = 1000, //ī�� 2�� �������� �ϳ��� ������ �ð� 
};

class CardManager
{
private:
	static CardManager* m_pInstance;

	//std::vector<Card*> cardList;
	Card cardList[SHOW_CARD_RANGE];

	int iRandList[SHOW_CARD_RANGE]; //count*2 ��ŭ�� i�� �迭�� ���� �̸� �� ����д�.
	int iRandOrder[IMAGE_COUNT] = { 0, }; //ī�� ���� ���� ����

	std::queue<int> queue_iRandOrder; //���� ���� üũ�� //ex)4,2,0,1,3 (�̹��� �׸��� ID)
	int turnNextID; //���������� ������ ���� ID�� ����
	int FrontCount; //�ո��� ī�� ����
	int sameCheck[CARD_END] = { 0, }; //���� ī�� üũ

	//���� ���� ���� �迭 ����
	void CreateRandNum(int* list, int range);

	//ī�� �迭�� xy��ǥ ���� - 0~5 �������. �տ������� ������(ī�� ���� �����ٶ�)
	void Set_ListXY_Order(int* list, int range);
	//ī�� �迭�� xy��ǥ ���� - ������ 0~5 �������. ���� ��ǥ ������(ī�� ���� ����)
	void Set_ListXY_Rand(int* list, int range);

	CardManager();
public:
	~CardManager();

	static CardManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new CardManager;
		return m_pInstance;
	}

	void CardInit(BitMapManager* BitMapMgr_Main);
	//ī�� index 0���� ���
	void ShowCard_Index(HDC hdc);
	//ī�� xy ������� ���
	void ShowCard_XY(HDC hdc);


	//ī�� �������� ����(��ǥ)
	void CardShuffleMix();
	//ī�� �ѹ��� ������(2�� �����⿡���� ���. �� �Ѿ �� ī�� ���� �ʱ�ȭ������ ���)
	void CardTurn_All(CARD _eCardState);
	//ī�� ���������� ������ //ī�� �� > �� ������ �� ���������� true ����
	bool CardTurn_Order(SEQUENCE sequence);

	//ī�� ���� ���� ����
	void CardOrderSet();
	//���� ī�� 2�� �ո� ���¸� ��Ȱ��ȭ(ī�� ���� �������� ������)
	//¦ Ʋ���� false���� > ���� GMM���� -2��
	bool CardInactiveCheck();
	//�ո� �̹��� ������ �ϴ� �Լ�
	void Front_IMG_Change(BitMapManager* BitMapMgr_Main);


	//ī�� �� > �� ������ + ī�� �ι� �� ������ + ī�� ���߸� ������� �ð� üũ ����
	bool CardList_ColliderCheck(POINT point, HWND hWnd_Main, TIMER TIMER_ID_CARD_ALL, TIMER TIMER_CARD_ALL_SEC, TIMERPROC timerFunc);
	//ī�带 �ϳ��� ������ ��, �� ������ ���� ī�带 ������. �ٽ� ó������ ī�带 �������� �ʱ�ȭ 
	void Set_TurnNextID_To_0() { turnNextID = 0; };
	//ī�带 �� ������� Ȯ��
	bool EmptyCardCheck();
};

