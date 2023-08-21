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
    case 0: //문 열기(Active)
        ChangeActiveState();

        //현재 상태에 따라 열고 닫고
        if (isActive)
        {
            GameMgr->Set_IsCurtainOpen(true);
            GameMgr->SetShowUnder(CURTAIN_OPEN);
        }
        else
        {
            GameMgr->Set_IsCurtainOpen(false);
            GameMgr->SetShowUnder(CURTAIN_CLOSE);
        }
    defualt:
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}