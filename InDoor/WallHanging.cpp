#include "WallHanging.h"
#include "GameManager.h"

WallHanging::WallHanging()
{
}

WallHanging::WallHanging(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

WallHanging::~WallHanging()
{
}

VOID WallHanging::Initialize()
{
    return VOID();
}

VOID WallHanging::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void WallHanging::DetailSelect(int selectNum)
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