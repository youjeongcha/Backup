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
	//���ٷθ� for�� ����(5)//�����Ҵ��� ���ָ� cardList[i], cardList[i+5]�� �ʱ�ȭ �� �� �ִ�.
	for (int i = 0; i < IMAGE_COUNT; i++) //10�� ī��� �̹��� ��Ʈ�� ����
	{
		//cardList.push_back(new Card); //TODO::�����Ҵ� ���� �ʰ� �迭��
		cardList[i] = Card();
		cardList[i].Init(BitMapMgr_Main, IMAGE(i), CARD_FIRST_X + i * CARD_NEXT_X, CARD_FIRST_Y); //TODO::ī�� ��� xy��ǥ 

		cardList[i + IMAGE_COUNT] = Card();
		cardList[i + IMAGE_COUNT].Init(BitMapMgr_Main, IMAGE(i), CARD_FIRST_X + i * CARD_NEXT_X, CARD_FIRST_Y); //TODO::ī�� ��� xy��ǥ 
	}
}

void CardManager::Front_IMG_Change(BitMapManager* BitMapMgr_Main)
{
	int IMG_ID;
	//TODO::���ٷθ� for�� ����(5) cardList[i+5]�� �ʱ�ȭ �� �� �ִ�.
	for (int i = 0; i < IMAGE_COUNT; i++) //10�� ī��� �̹��� ��Ʈ�� ����
	{
		cardList[i].Set_Front_IMG(BitMapMgr_Main, IMAGE(i));  //�Լ� �ȿ��� ó��. bitMap �ҷ����� 20~24�� �ϰ�. ȣ���� 6~10���� ��
		cardList[i + IMAGE_COUNT].Set_Front_IMG(BitMapMgr_Main, IMAGE(i));
	}
}

void CardManager::ShowCard_Index(HDC hdc)
{//ī�� index 0���� ���
	for (auto& show : cardList)
		show.Draw(hdc);
}

void CardManager::ShowCard_XY(HDC hdc)
{//xy ������� ���
	for (int i = 0; i < queue_iRandOrder.size(); i++)
		cardList[iRandOrder[i]].Draw(hdc);
}

void CardManager::CreateRandNum(int* list, int range)
{
	turnNextID = 0;

	int iRandTmp; //���� �� �ӽ� ����

	std::vector<int> v;

	for (int i = 0; i < range; i++)
		v.push_back(i);

	//���� �� �̱�(�ߺ�X)
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
	//list[i] : ī�� ID �ε��� ��ȣ
	//cardList[list[i]] : ī�� �ε��� ��ȣ ������� ���� (ex. 4,2,0,1)
	//set_randXY�� i�� �־�� ������� ��ġ�� �����ϴ�
}

void CardManager::Set_ListXY_Rand(int* list, int range)
{//������ ���� ��ġ�� ���� ��ġ
	int line_X, line_Y; //��� ����(ù°, ��° ��)

	for (int i = 0; i < range; i++)
	{
		if (list[i] >= IMAGE_COUNT)
		{//if ���� 5���� �Ѿ�� y��ǥ�� �ϳ� ������.
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
	//���� ���� - ���� �� �̱�
	CreateRandNum(iRandOrder, IMAGE_COUNT);

	for (int i = 0; i < IMAGE_COUNT; i++)
		queue_iRandOrder.push(iRandOrder[i]);

	//���� ������� ī�� ��ġ
	Set_ListXY_Order(iRandOrder, IMAGE_COUNT);
}

void CardManager::CardShuffleMix()
{
	//ó�� �ʱ�ȭ�϶��� ���� ���� ���ϱ�
	CreateRandNum(iRandList, SHOW_CARD_RANGE);
	
	//ī�� ���� ��ġ
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
		cardList[turnNextID].Set_CardState(CARD_REAR); //6���� �ٷ� 8�� �Ѿ��.
		break;
	}

	turnNextID++; //���̷��� ���� ���δ� ���� �������� ����.
	FrontCount--;

	if (FrontCount)
		return true; //������ �� �����ִ�.

	return false;
}




bool CardManager::CardInactiveCheck()
{
	int this_ID_Gap = sameCheck[FRONT_ID1] - sameCheck[FRONT_ID2]; //���� ī���� ID�� ���� ���� 5�� -5�� ���´�.
	int card_ID_Gap = IMAGE_COUNT;
	int order = queue_iRandOrder.front();
	
	//abs() �������� ���� ī������ Ȯ��
	if (abs(this_ID_Gap) == card_ID_Gap) 
	{
		//ī�� ������� Ŭ���ߴ��� Ȯ��
		if (order == sameCheck[FRONT_ID2] ||
			order == sameCheck[FRONT_ID1])
		{
			//���� ī�� ��Ȱ��ȭ(ȭ��� ����X)
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
	if (FrontCount < FRONT_COUNT_2) //ī�� �ո��� �ΰ��̸� �� ������ �ؾ��Ѵ�.
	{
		for (int i = 0; i < SHOW_CARD_RANGE; i++)
		{
			if (cardList[i].IsActive() &&  cardList[i].ColliderCheck(point))
			{
				//�ո��� ī�带 �� ��ġ���� ��� > �ش� �Լ��� ó���� ���� �ʴ´�.
				if (FrontCount == 1 && sameCheck[0] == i)
					return false;

				FrontCount++;
				
				//ī�� �� > �� ������ üũ
				switch (FrontCount)
				{
				case FRONT_COUNT_2:
					sameCheck[FRONT_ID2] = i;
					SetTimer(hWnd_Main, TIMER_ID_CARD_ALL, TIMER_CARD_ALL_SEC, timerFunc); //ī�� �ϳ��� ������ �ð� üũ
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