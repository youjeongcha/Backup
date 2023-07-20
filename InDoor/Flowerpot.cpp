#include "Flowerpot.h"
#include "GameManager.h"

Flowerpot::Flowerpot()
{
   
}

Flowerpot::Flowerpot(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}

Flowerpot::~Flowerpot()
{
}

VOID Flowerpot::Initialize()
{
    return VOID();
}

VOID Flowerpot::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Flowerpot::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: //문 열기(Active) //TODO::수정 필요
        ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //노크 //TODO:: 하단창 뜨고 ... 혹은 NPC 대면
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
    ENGINE::GUIMgr->Set_IsPause(false);
}