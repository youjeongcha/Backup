#include "Player.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Player::Player()
{
    state = State::Idle;
    dir = Direction::Right;

    ENGINE::ResourceMgr->Load("Player.bmp");

    renderer = new ENGINE::SpriteRenderer("Player.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));

    ENGINE::InputComponent* input = new ENGINE::InputComponent;
    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
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


void Player::Inventory()
{
    // TODO::플레이어의 특수한 인벤토리 확인 동작
   // Character::CheckInventory(itemID);
}