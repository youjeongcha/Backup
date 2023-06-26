#include "Player.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Player::Player()
{
    state = State::Idle;
    dir = Direction::Right;
    isSpace = false;

    ENGINE::ResourceMgr->Load("Player.bmp");

    renderer = new ENGINE::SpriteRenderer("Player.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));

    ENGINE::InputComponent* input = new ENGINE::InputComponent;
    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_SPACE, [&]() {  isSpace = true; state = State::Idle; }, [&]() { isSpace = false; state = State::Idle; }); //
    AddComponent(input);

    /*
    state = State::Idle;
    dir = Direction::Right;

    vResources.push_back({ "Player_Idle.bmp",  SpritesX_Idle, SpritesY, {1.0f / SpritesX_Idle, 1.0f / SpritesY} });
    vResources.push_back({ "Player_Run.bmp", SpritesX, SpritesY,  {1.0f / SpritesX, 1.0f / SpritesY} });

    for (auto resource : vResources)
        ENGINE::ResourceMgr->Load(resource.name);
///

    renderer = new ENGINE::SpriteRenderer(vResources); //안에서[0]만 세팅해주고 있음
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);

    //vResources[0].divX
    //TODO::해당 스프라이트 나누는 함수 각 이미지마다 다르게 나와야 한다.
    //AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0].divX, vResources[0].divY)); //
    AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0])); //

    ENGINE::InputComponent* input = new ENGINE::InputComponent;
    //캐릭터가 뒤로 가다가 멈췄을때는 뒤를 보고 있어야 한다.
    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    AddComponent(input);
    */
}

Player::~Player()
{
}

VOID Player::Update(const FLOAT& deltaTime)
{
    Operate(this);

    //key를 떼면 state가 idle 상태로 벼한다. -> 스프라이트도 idle 상태로 변경되어야 한다.
    //renderer->ChangeSpritese(vResources[0]); //idle

    switch (state)
    {
    case State::Move:
        //renderer->ChangeSpritese(vResources[1]);
        //anim->SetChangeResouce(vResources[1]);
        Move(deltaTime);
        break;
    case State::Idle:
        if (isSpace) //스페이스를 누른 상태 bool 값
        {
            //가구 좌표와 크기 필요
        }

        //if (prevState == State::Move) //'0'은 move 상태일때
        //{
        //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
        //}
        break;
    }

    //스프라이트 왼오 나눠서 애니메이션 플레이
    switch (dir)
    {
    case Direction::Right:
        anim->Play(0 + (int)state * 2);
        break;
    case Direction::Left:
        anim->Play(1 + (int)state * 2);
        break;
    }

    prevState = state;
}


void Player::Inventory()
{
    // TODO::플레이어의 특수한 인벤토리 확인 동작
   // Character::CheckInventory(itemID);
}