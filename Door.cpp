#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"


//TODO::�����ڿ��� ���ڸ� �޾Ƽ� Object�� �󼼰��� �����ϴ� ������ �ٲٰ��� ��
//â���� ������ �� ��쿡 ������. �������� ������ ��ǥ�� �����ϴ� txt�� ���� ����?
Door::Door()
{
   // //������ isACtive�� ����� ���� ���� ��ȣ�ۿ� ���� üũ
   // name = "��";

 
   // typeCheck[OBJECT_TYPE::NORMAL] = false;
   // typeCheck[OBJECT_TYPE::MOVE] = false;
   // typeCheck[OBJECT_TYPE::ANIM] = false;
   // typeCheck[OBJECT_TYPE::ACTIVE] = true;

   // Available = false; //TODO:: ������ �ۿ��ϴ���. �ۿ� ���ϸ� �ٸ� ó��
   // isMove = false;
   // isAnim = false;
   // isActive = false;
   // //state = State::INACTIVE;

   // //dir = Direction::NONE;
   // //moveSpeed = 0;
   // 
   // //���ҽ�
   // SpritesX = 1;
   // SpritesY = 2;

   // ENGINE::ResourceMgr->Load("Home_Door.bmp");

   // renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
   // renderer->SetPos(650, 55);
   // renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
   // renderer->SetScale(transform->scale.x, transform->scale.y);
   // if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
   // {
   //     renderer->SetSrc(0, 1);
   // }
   // AddComponent(renderer);
   // 

   // //Anim ����
   // if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
   //     AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
   // else
   //     anim = NULL;

   // //Move ����
   // if (isMove)
   // {

   // }
   // else
   // {
   //     dir = Direction::NONE; //�̰� 
   //     moveSpeed = 0;
   // }

   ///* ENGINE::InputComponent* input = new ENGINE::InputComponent;
   // input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
   // input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
   // AddComponent(input);*/
}

Door::Door(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}



Door::~Door()
{
}

VOID Door::Initialize()
{
    return VOID();
}

VOID Door::Move(const FLOAT& deltaTime)
{
    return VOID();
}
