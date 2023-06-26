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

    renderer = new ENGINE::SpriteRenderer(vResources); //�ȿ���[0]�� �������ְ� ����
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);

    //vResources[0].divX
    //TODO::�ش� ��������Ʈ ������ �Լ� �� �̹������� �ٸ��� ���;� �Ѵ�.
    //AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0].divX, vResources[0].divY)); //
    AddComponent(anim = new ENGINE::SpriteAnimation(vResources[0])); //

    ENGINE::InputComponent* input = new ENGINE::InputComponent;
    //ĳ���Ͱ� �ڷ� ���ٰ� ���������� �ڸ� ���� �־�� �Ѵ�.
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

    //key�� ���� state�� idle ���·� ���Ѵ�. -> ��������Ʈ�� idle ���·� ����Ǿ�� �Ѵ�.
    //renderer->ChangeSpritese(vResources[0]); //idle

    switch (state)
    {
    case State::Move:
        //renderer->ChangeSpritese(vResources[1]);
        //anim->SetChangeResouce(vResources[1]);
        Move(deltaTime);
        break;
    case State::Idle:
        if (isSpace) //�����̽��� ���� ���� bool ��
        {
            //���� ��ǥ�� ũ�� �ʿ�
        }

        //if (prevState == State::Move) //'0'�� move �����϶�
        //{
        //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
        //}
        break;
    }

    //��������Ʈ �޿� ������ �ִϸ��̼� �÷���
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
    // TODO::�÷��̾��� Ư���� �κ��丮 Ȯ�� ����
   // Character::CheckInventory(itemID);
}