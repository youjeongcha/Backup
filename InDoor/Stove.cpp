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
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0:
        GameMgr->SetShowUnder(COOK); //TODO::요리기능 추가
    defualt:
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}