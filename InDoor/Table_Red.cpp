#include "Table_Red.h"
#include "ResourceManager.h"

Table_Red::Table_Red()
{
}

Table_Red::Table_Red(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Table_Red::~Table_Red()
{
}

VOID Table_Red::Initialize()
{
    return VOID();
}

VOID Table_Red::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Table_Red::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: //�� ����(Active) //TODO::���� �ʿ�
        // ChangeActiveState();
         //return std::bind(&Door::ChangeActiveState, this);
    case 1: //��ũ //TODO:: �ϴ�â �߰� ... Ȥ�� NPC ���
        break;
    }

    //return nullptr; // ���� ó��: ������ �����ʸ� ã�� ���� ���
}