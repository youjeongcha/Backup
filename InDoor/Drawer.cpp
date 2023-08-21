#include "Drawer.h"
#include "GameManager.h"

Drawer::Drawer()
{
    Initialize();
}

Drawer::Drawer(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    Initialize();
}

Drawer::~Drawer()
{
}

VOID Drawer::Initialize()
{
    isHaveItem = true;
}

VOID Drawer::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Drawer::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: 
        //���谡 �־�� �� �� �ִ�.
        if (GameMgr->MinusPlayerItem(KEY)) 
        {
            if (isHaveItem)
            {
                GameMgr->SetShowUnder(DRAWER_IN_O); //�������� ������ ������ �� �ְ�
                GameMgr->PlusPlayerInventory({ SEED_BLUE, 1 });
                isHaveItem = false;
            }

        }
        else
        {
            //���� �ѹ� ���� ���� �η����� �ٽ� �� ����.
            if (!isHaveItem)
                GameMgr->SetShowUnder(DRAWER_OPEN_O);
            else
                GameMgr->SetShowUnder(DRAWER_OPEN_X);
        }
       
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}
