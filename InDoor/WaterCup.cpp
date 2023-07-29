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
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0:
        GameMgr->SetShowUnder(WATER_O); //�������� ������ ������ �� �ְ�
        GameMgr->PlusPlayerInventory(std::make_pair(WATER, 1));
        isUse = false;
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}