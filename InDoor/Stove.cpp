#include "Stove.h"
#include "GameManager.h"

Stove::Stove()
{
}

Stove::Stove(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

Stove::~Stove()
{
}

VOID Stove::Initialize()
{
    return VOID();
}

VOID Stove::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Stove::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0:
        GameMgr->SetShowUnder(COOK); //TODO::�丮��� �߰�
    defualt:
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}