#include "CardManager.h"

CardManager* CardManager::m_pInstance = NULL;

CardManager::CardManager()
{
	FrontCount = SHOW_CARD_RANGE;
	turnNextID = 0;
}

CardManager::~CardManager()
{
	for (auto i : cardList)
		delete& i;
}

void CardManager::CardInit(BitMapManager* BitMapMgr_Main)
{
	int IMG_ID;
	//한줄로만 for문 돌고(5)//동적할당을 없애면 cardList[i], cardList[i+5]를 초기화 할 수 있다.
	for (int i = 0; i < IMAGE_COUNT; i++) //10개 카드들 이미지 비트맵 설정
	{
		//cardList.push_back(new Card); //TODO::동적할당 하지 않고 배열로
		cardList[i] = Card();
		cardList[i].Init(BitMapMgr_Main, IMAGE(i), CARD_FIRST_X + i * CARD_NEXT_X, CARD_FIRST_Y); //TODO::카드 출력 xy좌표 

		cardList[i + IMAGE_COUNT] = Card();
		cardList[i + IMAGE_COUNT].Init(BitMapMgr_Main, IMAGE(i), CARD_FIRST_X + i * CARD_NEXT_X, CARD_FIRST_Y); //TODO::카드 출력 xy좌표 
	}
}

void CardManager::Front_IMG_Change(BitMapManager* BitMapMgr_Main)
{
	int IMG_ID;
	//TODO::한줄로만 for문 돌고(5) cardList[i+5]를 초기화 할 수 있다.
	for (int i = 0; i < IMAGE_COUNT; i++) //10개 카드들 이미지 비트맵 설정
	{
		cardList[i].Set_Front_IMG(BitMapMgr_Main, IMAGE(i));  //함수 안에서 처리. bitMap 불러오기 20~24로 하고. 호출은 6~10으로 함
		cardList[i + IMAGE_COUNT].Set_Front_IMG(BitMapMgr_Main, IMAGE(i));
	}
}

void CardManager::ShowCard_Index(HDC hdc)
{//카드 index 0부터 출력
	for (auto& show : cardList)
		show.Draw(hdc);
}

void CardManager::ShowCard_XY(HDC hdc)
{//xy 순서대로 출력
	for (int i = 0; i < queue_iRandOrder.size(); i++)
		cardList[iRandOrder[i]].Draw(hdc);
}

void CardManager::CreateRandNum(int* list, int range)
{
	turnNextID = 0;

	int iRandTmp; //랜덤 수 임시 저장

	std::vector<int> v;

	for (int i = 0; i < range; i++)
		v.push_back(i);

	//랜덤 수 뽑기(중복X)
	for (int i = 0; i < range; i++)
	{
		iRandTmp = rand() % v.size();
		list[i] = v[iRandTmp];
		v.erase(v.begin() + iRandTmp);
	}
}

void CardManager::Set_ListXY_Order(int* list, int range)
{
	for (int i = 0; i < range; i++)
		cardList[list[i]].Set_RandXY(CARD_FIRST_X + i * CARD_NEXT_X, CARD_FIRST_Y);
	//list[i] : 카드 ID 인덱스 번호
	//cardList[list[i]] : 카드 인덱스 번호 순서대로 진행 (ex. 4,2,0,1)
	//set_randXY에 i를 넣어야 순서대로 배치가 가능하다
}

void CardManager::Set_ListXY_Rand(int* list, int range)
{//정해진 랜덤 위치에 따라 배치
	int line_X, line_Y; //출력 라인(첫째, 둘째 줄)

	for (int i = 0; i < range; i++)
	{
		if (list[i] >= IMAGE_COUNT)
		{//if 한줄 5장이 넘어가면 y좌표를 하나 내린다.
			line_X = CARD_FIRST_X + (list[i] - IMAGE_COUNT) * CARD_NEXT_X;
			line_Y = CARD_FIRST_Y + CARD_NEXT_Y;
		}
		else
		{
			line_X = CARD_FIRST_X + list[i] * CARD_NEXT_X;
			line_Y = CARD_FIRST_Y;
		}

		cardList[i].Set_RandXY(line_X, line_Y);
	}
}

void CardManager::CardOrderSet()
{
	//맞출 순서 - 랜덤 수 뽑기
	CreateRandNum(iRandOrder, IMAGE_COUNT);

	for (int i = 0; i < IMAGE_COUNT; i++)
		queue_iRandOrder.push(iRandOrder[i]);

	//맞출 순서대로 카드 배치
	Set_ListXY_Order(iRandOrder, IMAGE_COUNT);
}

void CardManager::CardShuffleMix()
{
	//처음 초기화일때만 랜덤 순서 정하기
	CreateRandNum(iRandList, SHOW_CARD_RANGE);
	
	//카드 랜덤 배치
	Set_ListXY_Rand(iRandList, SHOW_CARD_RANGE);
}

void CardManager::CardTurn_All(CARD _eCardState)
{
	for (int i = 0; i < SHOW_CARD_RANGE; i++)
		cardList[i].Set_CardState(_eCardState);

	switch (_eCardState)
	{
	case CARD_FRONT:
		FrontCount = SHOW_CARD_RANGE;
		break;
	default:
		FrontCount = 0;
		break;
	}
}

bool CardManager::CardTurn_Order(SEQUENCE sequence)
{

	switch (sequence)
	{
	case SEQUENCE_SHOWCARD:
		cardList[iRandOrder[turnNextID]].Set_CardState(CARD_REAR);
		break;
	default:
		cardList[turnNextID].Set_CardState(CARD_REAR); //6에서 바로 8로 넘어가고.
		break;
	}

	turnNextID++; //★이렇게 따로 빼두는 쪽이 가독성이 좋다.
	FrontCount--;

	if (FrontCount)
		return true; //뒤집을 게 남아있다.

	return false;
}




bool CardManager::CardInactiveCheck()
{
	int this_ID_Gap = sameCheck[FRONT_ID1] - sameCheck[FRONT_ID2]; //같은 카드의 ID를 서로 빼면 5나 -5가 나온다.
	int card_ID_Gap = IMAGE_COUNT;
	int order = queue_iRandOrder.front();
	
	//abs() 절댓값으로 같은 카드인지 확인
	if (abs(this_ID_Gap) == card_ID_Gap) 
	{
		//카드 순서대로 클릭했는지 확인
		if (order == sameCheck[FRONT_ID2] ||
			order == sameCheck[FRONT_ID1])
		{
			//맞춘 카드 비활성화(화면상에 노출X)
			cardList[sameCheck[FRONT_ID1]].Set_Inactive();
			cardList[sameCheck[FRONT_ID2]].Set_Inactive();

			queue_iRandOrder.pop();
			return true;
		}
	}
	return false;
}

bool CardManager::CardList_ColliderCheck(POINT point, HWND hWnd_Main, TIMER TIMER_ID_CARD_ALL, TIMER TIMER_CARD_ALL_SEC, TIMERPROC timerFunc)
{
	if (FrontCount < FRONT_COUNT_2) //카드 앞면이 두개이면 안 눌리게 해야한다.
	{
		for (int i = 0; i < SHOW_CARD_RANGE; i++)
		{
			if (cardList[i].IsActive() &&  cardList[i].ColliderCheck(point))
			{
				//앞면인 카드를 또 터치했을 경우 > 해당 함수의 처리를 하지 않는다.
				if (FrontCount == 1 && sameCheck[0] == i)
					return false;

				FrontCount++;
				
				//카드 앞 > 뒷 돌리기 체크
				switch (FrontCount)
				{
				case FRONT_COUNT_2:
					sameCheck[FRONT_ID2] = i;
					SetTimer(hWnd_Main, TIMER_ID_CARD_ALL, TIMER_CARD_ALL_SEC, timerFunc); //카드 하나씩 뒤집기 시간 체크
				default:
					sameCheck[FRONT_ID1] = i;
				}

				return true;
			}
		}
	}
	return false;
}


bool CardManager::EmptyCardCheck()
{
	if (queue_iRandOrder.size() == 0)
		return true;

	return false;
}