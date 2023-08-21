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
    case 0: //�� ����(Active)
        ChangeActiveState();

        //���� ���¿� ���� ���� �ݰ�
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