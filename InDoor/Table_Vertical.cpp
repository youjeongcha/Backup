#include "Table_Vertical.h"
#include "GameManager.h"

Table_Vertical::Table_Vertical()
{
}

Table_Vertical::Table_Vertical(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Table_Vertical::~Table_Vertical()
{
}

VOID Table_Vertical::Initialize()
{
    return VOID();
}

VOID Table_Vertical::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Table_Vertical::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    //switch (selectNum)
    //{
    //case 0: //�� ����(Active) //TODO::���� �ʿ�
    //    ChangeActiveState();
    //    //return std::bind(&Door::ChangeActiveState, this);
    //case 1: //��ũ //TODO:: �ϴ�â �߰� ... Ȥ�� NPC ���
    //    break;
    //}

    detailSelect_UI->SetEnable(FALSE);
    GameMgr->Set_IsPause(false);
}