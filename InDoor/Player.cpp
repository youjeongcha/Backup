#include "Player.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Player::Player()
{
    state = State::Idle;
    dir = Direction::Right;

    ENGINE::ResourceMgr->Load("Player_Idle.bmp");
    vResources.push_back({ "Player_Idle.bmp",  SpritesX_Idle, SpritesY, {1.0f / SpritesX_Idle, 1.0f / SpritesY} });

    ENGINE::ResourceMgr->Load("Player_Run.bmp");
    vResources.push_back({ "Player_Run.bmp", SpritesX, SpritesY,  {1.0f / SpritesX, 1.0f / SpritesY} });

///

    renderer = new ENGINE::SpriteRenderer(vResources);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer); //TODO::��������Ʈ �������� �ѹ��� ���ļ� �ְ� �Ǵµ�

    //vResources[0].divX
    //TODO::�ش� ��������Ʈ ������ �Լ� �� �̹������� �ٸ��� ���;� �Ѵ�.
    //AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0].divX, vResources[0].divY)); //
    AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0])); //

    ENGINE::InputComponent* input = new ENGINE::InputComponent;
    //ĳ���Ͱ� �ڷ� ���ٰ� ���������� �ڸ� ���� �־�� �Ѵ�.
    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    AddComponent(input);
}

Player::~Player()
{
}


void Player::Inventory()
{
    // TODO::�÷��̾��� Ư���� �κ��丮 Ȯ�� ����
   // Character::CheckInventory(itemID);
}