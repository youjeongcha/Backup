#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"

Door::Door()
{
    //������ isACtive�� ����� ���� ���� ��ȣ�ۿ� ���� üũ
    name = "��";
 
    typeCheck[OBJECT_TYPE::NORMAL] = false;
    typeCheck[OBJECT_TYPE::MOVE] = false;
    typeCheck[OBJECT_TYPE::ANIM] = false;
    typeCheck[OBJECT_TYPE::ACTIVE] = true;

    Available = false;
    isMove = false;
    isAnim = false;
    isActive = false;
    //state = State::INACTIVE;

    dir = Direction::NONE;
    moveSpeed = 0;
    
    //���ҽ�
    SpritesX = 1;
    SpritesY = 1;

    ENGINE::ResourceMgr->Load("Home_Door.bmp");

    renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    

    //Anim ����
    if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move ����
    if (isMove)
    {
        dir = Direction::NONE; //�̰� 
        moveSpeed = 0;
    }

   /* ENGINE::InputComponent* input = new ENGINE::InputComponent;
    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    AddComponent(input);*/
}

Door::~Door()
{
}
