#include "Curtain_Red.h"
#include "GameManager.h"

Curtain_Red::Curtain_Red()
{
}

Curtain_Red::Curtain_Red(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Curtain_Red::~Curtain_Red()
{
}

VOID Curtain_Red::Initialize()
{
    return VOID();
}

VOID Curtain_Red::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Curtain_Red::DetailSelect(int selectNum)
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