#include "Sideboard.h"
#include "GameManager.h"

Sideboard::Sideboard()
{
}

Sideboard::Sideboard(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

Sideboard::~Sideboard()
{
}

VOID Sideboard::Initialize()
{
    return VOID();
}

VOID Sideboard::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Sideboard::DetailSelect(int selectNum)
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