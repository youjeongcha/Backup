#include "OneCandle.h"
#include "GameManager.h"

OneCandle::OneCandle()
{
}

OneCandle::OneCandle(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

OneCandle::~OneCandle()
{
}

VOID OneCandle::Initialize()
{
}

VOID OneCandle::Move(const FLOAT& deltaTime)
{
    return VOID();
}

//void OneCandle::Animation(const FLOAT& deltaTime)
//{
//    //�ִϸ��̼��� ������ Ȱ��ȭ �����϶� ���ȴ�.
//    if ((isAnim && isActive) && (anim != nullptr))
//    {
//        Operate(this);
//        anim->Play(1);
//    }
//}

void OneCandle::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: //�� ����(Active)
        ChangeActiveState();

        //���� ���¿� ���� ���� �ݰ�
        if (isActive)
        {
            isAnim = true;
            GameMgr->SetShowUnder(ONECANDLE_O);
        }
        else
        {
            isAnim = false;
            anim->Stop();
            GameMgr->SetShowUnder(ONECANDLE_X);
        }
    defualt:
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}