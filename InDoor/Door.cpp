#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"

Door::Door()
{
    //문에서 isACtive는 사람과 문을 통해 상호작용 가능 체크
    name = "문";
 
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
    
    //리소스
    SpritesX = 1;
    SpritesY = 1;

    ENGINE::ResourceMgr->Load("Home_Door.bmp");

    renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    

    //Anim 관련
    if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move 관련
    if (isMove)
    {
        dir = Direction::NONE; //이거 
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
