#include "Bed.h"
#include "ResourceManager.h"

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
    case 0: //�� ����(Active) //TODO::���� �ʿ�
        //ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //��ũ //TODO:: �ϴ�â �߰� ... Ȥ�� NPC ���
        break;
    }

    //return nullptr; // ���� ó��: ������ �����ʸ� ã�� ���� ���
}
