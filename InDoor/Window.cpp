#include "Window.h"
#include "GameManager.h"

Window::Window()
{
}

Window::Window(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    //FSM* fsm;
    //m_nID = fsm->Get_NextVaildID();
}

Window::~Window()
{
}

VOID Window::Initialize()
{
    return VOID();
}

VOID Window::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Window::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0:
      //  if (GameMgr->Get_IsCurtainOpen())
        {
            GameMgr->GetTimeLabel()->SetEnable(false);
            GameMgr->Set_IsShowWindow(true);
        }
        //else
        //    GameMgr->SetShowUnder(WIDNOW_OPEN_X);
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
    //GameMgr->Set_IsPause(false);
}
