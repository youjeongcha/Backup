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
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    ////취소 제외 최대 선택지 개수는 3개로 제한
    //switch (selectNum)
    //{
    //case 0:
    //    GameMgr->SetShowUnder(CLOSET_IN_O); //TODO::아이템이 있으면 가져갈 수 있게
    //defualt:
    //    break;
    //}

    //detailSelect_UI->SetEnable(FALSE);
}