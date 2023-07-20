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