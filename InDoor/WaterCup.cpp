#include "WaterCup.h"
#include "GameManager.h"

WaterCup::WaterCup()
{
    //Initialize();
}

WaterCup::WaterCup(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //Initialize();
}

WaterCup::~WaterCup()
{
}


VOID WaterCup::Initialize()
{
    //isHave = true;
}

VOID WaterCup::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void WaterCup::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0:
        GameMgr->SetShowUnder(WATER_O); //아이템이 있으면 가져갈 수 있게
        GameMgr->PlusPlayerInventory(std::make_pair(WATER, 1));
        isUse = false;
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}