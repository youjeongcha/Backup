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
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: 
        if (isHaveItem)
        {
            GameMgr->SetShowUnder(CLOSET_IN_O); //아이템이 있으면 가져갈 수 있게
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