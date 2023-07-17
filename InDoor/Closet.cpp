#include "Closet.h"
#include "ResourceManager.h"

Closet::Closet()
{
}

Closet::Closet(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Closet::~Closet()
{
}

VOID Closet::Initialize()
{
    return VOID();
}

VOID Closet::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Closet::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: //문 열기(Active) //TODO::수정 필요
       // ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //노크 //TODO:: 하단창 뜨고 ... 혹은 NPC 대면
        break;
    }

    //return nullptr; // 예외 처리: 적절한 리스너를 찾지 못한 경우
}