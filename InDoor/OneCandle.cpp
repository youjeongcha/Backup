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
//    //애니메이션은 가구가 활성화 상태일때 사용된다.
//    if ((isAnim && isActive) && (anim != nullptr))
//    {
//        Operate(this);
//        anim->Play(1);
//    }
//}

void OneCandle::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: //문 열기(Active)
        ChangeActiveState();

        //현재 상태에 따라 열고 닫고
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