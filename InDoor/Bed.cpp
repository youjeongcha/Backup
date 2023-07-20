#include "Bed.h"
#include "GameManager.h"

Bed::Bed()
{
}

Bed::Bed(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Bed::~Bed()
{
}

VOID Bed::Initialize()
{
    return VOID();
}

VOID Bed::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Bed::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: 
        Sleep();
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
    //ENGINE::GUIMgr->Set_IsPause(false);
}

void Bed::Sleep()
{
    GameMgr->PlayerSleep();
}


