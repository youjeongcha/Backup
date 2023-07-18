#include "Bed.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Player.h"

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

    //return nullptr; // ���� ó��: ������ �����ʸ� ã�� ���� ���
}

void Bed::Sleep()
{
    GameMgr->PlayerSleep();
}


