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
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: //�� ����(Active) //TODO::���� �ʿ�
        ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //��ũ //TODO:: �ϴ�â �߰� ... Ȥ�� NPC ���
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
    ENGINE::GUIMgr->Set_IsPause(false);
}