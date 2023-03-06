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
	//카드 초기화(이미지 넣기)CardInit, 셔플CardShuffleMix, 카드 보여주기 후 뒤집기 + 앞면 숫자 설정에 사용CardTurn_All.
	SHOW_CARD_RANGE = IMAGE_COUNT * 2,
	//색 출력 망한 이미지
	SHOW_CHANGE_CARD_RANGE = SHOW_CARD_RANGE + IMAGE_CHANGE_TIGER,

	SHOW_ONELINE = 5, //한줄에 보여줄 카드 수
};

enum SEQUENCE
{
	SEQUENCE_MENU,
	SEQUENCE_STROY,
	SEQUENCE_RABBIT,
	SEQUENCE_SHOWCARD, //카드 순서 보여주기
	SEQUENCE_CARD_ORDERTURN, //본 게임 전체 카드 뒤집어지는 씬
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
	TIMER_ID_CARD_ORDER, //카드 전부 순서대로 뒤집을때
	TIMER_ID_CARD_ALL, //카드 2개 한번에 뒤집을때

	TIMER_SCENE_SEC = 1000,
	TIMER_CARD_ODER_SEC = 1000, //카드 전부 뒤집을때 하나씩 뒤집을 시간
	TIMER_CARD_ALL_SEC = 1000, //카드 2개 뒤집을때 하나씩 뒤집을 시간 
};

class CardManager
{
private:
	static CardManager* m_pInstance;

	//std::vector<Card*> cardList;
	Card cardList[SHOW_CARD_RANGE];

	int iRandList[SHOW_CARD_RANGE]; //count*2 만큼의 i를 배열로 만들어서 미리 다 섞어둔다.
	int iRandOrder[IMAGE_COUNT] = { 0, }; //카드 맞출 순서 생성

	std::queue<int> queue_iRandOrder; //맞춤 순서 체크용 //ex)4,2,0,1,3 (이미지 그림의 ID)
	int turnNextID; //순차적으로 뒤집을 다음 ID를 저장
	int FrontCount; //앞면인 카드 갯수
	int sameCheck[CARD_END] = { 0, }; //동일 카드 체크

	//랜덤 섞을 랜덤 배열 생성
	void CreateRandNum(int* list, int range);

	//카드 배열의 xy좌표 결정 - 0~5 순서대로. 앞에서부터 뒤집기(카드 순서 보여줄때)
	void Set_ListXY_Order(int* list, int range);
	//카드 배열의 xy좌표 결정 - 지정된 0~5 순서대로. 랜덤 좌표 뒤집기(카드 게임 들어갈때)
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
	//카드 index 0부터 출력
	void ShowCard_Index(HDC hdc);
	//카드 xy 순서대로 출력
	void ShowCard_XY(HDC hdc);


	//카드 랜덤으로 섞기(좌표)
	void CardShuffleMix();
	//카드 한번에 뒤집기(2개 뒤집기에서도 사용. 씬 넘어갈 때 카드 상태 초기화에서도 사용)
	void CardTurn_All(CARD _eCardState);
	//카드 순차적으로 뒤집기 //카드 앞 > 뒤 뒤집을 게 남아있으면 true 리턴
	bool CardTurn_Order(SEQUENCE sequence);

	//카드 맞출 순서 생성
	void CardOrderSet();
	//같은 카드 2개 앞면 상태면 비활성화(카드 도로 뒤집어질 시점에)
	//짝 틀리면 false리턴 > 이후 GMM에서 -2초
	bool CardInactiveCheck();
	//앞면 이미지 설정만 하는 함수
	void Front_IMG_Change(BitMapManager* BitMapMgr_Main);


	//카드 뒷 > 앞 뒤집기 + 카드 두번 안 눌리게 + 카드 맞추면 사라지는 시간 체크 시작
	bool CardList_ColliderCheck(POINT point, HWND hWnd_Main, TIMER TIMER_ID_CARD_ALL, TIMER TIMER_CARD_ALL_SEC, TIMERPROC timerFunc);
	//카드를 하나씩 뒤집을 때, 맨 마지막 남은 카드를 뒤집고. 다시 처음부터 카드를 뒤집을때 초기화 
	void Set_TurnNextID_To_0() { turnNextID = 0; };
	//카드를 다 맞췄는지 확인
	bool EmptyCardCheck();
};

