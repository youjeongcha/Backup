#include "KitchenCounter.h"
#include "GameManager.h"

KitchenCounter::KitchenCounter()
{
}

KitchenCounter::KitchenCounter(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

KitchenCounter::~KitchenCounter()
{
}

VOID KitchenCounter::Initialize()
{
    return VOID();
}

VOID KitchenCounter::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void KitchenCounter::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    ////��� ���� �ִ� ������ ������ 3���� ����
    //switch (selectNum)
    //{
    //case 0:
    //    GameMgr->SetShowUnder(CLOSET_IN_O); //TODO::�������� ������ ������ �� �ְ�
    //defualt:
    //    break;
    //}

    //detailSelect_UI->SetEnable(FALSE);
}