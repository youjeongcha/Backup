#include "FirePot.h"
#include "GameManager.h"

FirePot::FirePot()
{
}

FirePot::FirePot(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

FirePot::~FirePot()
{
}

VOID FirePot::Initialize()
{
    return VOID();
}

VOID FirePot::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void FirePot::DetailSelect(int selectNum)
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