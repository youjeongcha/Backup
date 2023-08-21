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
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: 
        //열쇠가 있어야 열 수 있다.
        if (GameMgr->MinusPlayerItem(KEY)) 
        {
            if (isHaveItem)
            {
                GameMgr->SetShowUnder(DRAWER_IN_O); //아이템이 있으면 가져갈 수 있게
                GameMgr->PlusPlayerInventory({ SEED_BLUE, 1 });
                isHaveItem = false;
            }

        }
        else
        {
            //서랍 한번 열면 열쇠 부러져서 다시 못 연다.
            if (!isHaveItem)
                GameMgr->SetShowUnder(DRAWER_OPEN_O);
            else
                GameMgr->SetShowUnder(DRAWER_OPEN_X);
        }
       
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}
