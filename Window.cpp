#include "Window.h"
#include "ResourceManager.h"
//#include "SceneManager.h"

Window::Window()
{
    ////문에서 isACtive는 사람과 문을 통해 상호작용 가능 체크
    //name = "창문";


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

    ////리소스
    //SpritesX = 1;
    //SpritesY = 2;

    //ENGINE::ResourceMgr->Load("Home_Window.bmp");

    //renderer = new ENGINE::SpriteRenderer("Home_Window.bmp", SpritesX, SpritesY);
    //renderer->SetPos(450, 32);
    //renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    //renderer->SetScale(transform->scale.x, transform->scale.y);
    //if (isActive) //작동 여부에 따라 이미지 다르게
    //{
    //    renderer->SetSrc(0, 1);
    //}
    //AddComponent(renderer);


    ////Anim 관련
    //if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
    //    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    //else
    //    anim = NULL;

    ////Move 관련
    //if (isMove)
    //{

    //}
    //else
    //{
    //    dir = Direction::NONE; //이거 
    //    moveSpeed = 0;
    //}

    ///* ENGINE::InputComponent* input = new ENGINE::InputComponent;
    // input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    // input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    // AddComponent(input);*/
}

Window::Window(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

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
