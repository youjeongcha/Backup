#include "Drawer.h"
#include "GameManager.h"

Drawer::Drawer()
{
    ////������ isACtive�� ����� ���� ���� ��ȣ�ۿ� ���� üũ
    //name = "â��";


    //typeCheck[OBJECT_TYPE::NORMAL] = false;
    //typeCheck[OBJECT_TYPE::MOVE] = false;
    //typeCheck[OBJECT_TYPE::ANIM] = false;
    //typeCheck[OBJECT_TYPE::ACTIVE] = true;

    //Available = true;
    //isMove = false;
    //isAnim = false;
    //isActive = true;

    ////state = State::INACTIVE;

    ///*dir = Direction::NONE;
    //moveSpeed = 0;*/

    ////���ҽ�
    //SpritesX = 1;
    //SpritesY = 2;

    //ENGINE::ResourceMgr->Load("Home_Window.bmp");

    //renderer = new ENGINE::SpriteRenderer("Home_Window.bmp", SpritesX, SpritesY);
    //renderer->SetPos(450, 32);
    //renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    //renderer->SetScale(transform->scale.x, transform->scale.y);
    //if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
    //{
    //    renderer->SetSrc(0, 1);
    //}
    //AddComponent(renderer);


    ////Anim ����
    //if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
    //    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    //else
    //    anim = NULL;

    ////Move ����
    //if (isMove)
    //{

    //}
    //else
    //{
    //    dir = Direction::NONE; //�̰� 
    //    moveSpeed = 0;
    //}

    ///* ENGINE::InputComponent* input = new ENGINE::InputComponent;
    // input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    // input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    // AddComponent(input);*/
}

Drawer::Drawer(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}

Drawer::~Drawer()
{
}

VOID Drawer::Initialize()
{
    return VOID();
}

VOID Drawer::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Drawer::DetailSelect(int selectNum)
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
