#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"


//TODO::생성자에서 인자를 받아서 Object의 상세값을 설정하는 쪽으로 바꾸고자 함
//창문을 여러개 달 경우에 관리는. 가구들을 개수와 좌표를 관리하는 txt가 따로 존재?
Door::Door()
{
   // //문에서 isACtive는 사람과 문을 통해 상호작용 가능 체크
   // name = "문";

 
   // typeCheck[OBJECT_TYPE::NORMAL] = false;
   // typeCheck[OBJECT_TYPE::MOVE] = false;
   // typeCheck[OBJECT_TYPE::ANIM] = false;
   // typeCheck[OBJECT_TYPE::ACTIVE] = true;

   // Available = false; //TODO:: 마땅히 작용하는지. 작용 안하면 다른 처리
   // isMove = false;
   // isAnim = false;
   // isActive = false;
   // //state = State::INACTIVE;

   // //dir = Direction::NONE;
   // //moveSpeed = 0;
   // 
   // //리소스
   // SpritesX = 1;
   // SpritesY = 2;

   // ENGINE::ResourceMgr->Load("Home_Door.bmp");

   // renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
   // renderer->SetPos(650, 55);
   // renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
   // renderer->SetScale(transform->scale.x, transform->scale.y);
   // if (isActive) //작동 여부에 따라 이미지 다르게
   // {
   //     renderer->SetSrc(0, 1);
   // }
   // AddComponent(renderer);
   // 

   // //Anim 관련
   // if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
   //     AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
   // else
   //     anim = NULL;

   // //Move 관련
   // if (isMove)
   // {

   // }
   // else
   // {
   //     dir = Direction::NONE; //이거 
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
