#include "Shelf_Book.h"
#include "GameManager.h"

Shelf_Book::Shelf_Book()
{
}

Shelf_Book::Shelf_Book(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Shelf_Book::~Shelf_Book()
{
}

VOID Shelf_Book::Initialize()
{
    return VOID();
}

VOID Shelf_Book::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Shelf_Book::DetailSelect(int selectNum)
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