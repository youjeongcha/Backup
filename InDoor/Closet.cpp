#include "Closet.h"
#include "GameManager.h"

Closet::Closet()
{
    Initialize();
}

Closet::Closet(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    Initialize();
}

Closet::~Closet()
{
}

VOID Closet::Initialize()
{
    isHaveItem = true;
}

VOID Closet::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Closet::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: 
        if (isHaveItem)
        {
            GameMgr->SetShowUnder(CLOSET_IN_O); //�������� ������ ������ �� �ְ�
            GameMgr->PlusPlayerInventory(std::make_pair(KEY, 1));
            isHaveItem = false;
        }
        else
        {
            GameMgr->SetShowUnder(CLOSET_IN_X);
        }
        break;
    defualt:
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}