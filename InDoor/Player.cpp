#include "Player.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"

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

VOID Player::Initialize()
{
    transform->position = { PLAYER_RESPON_BED,  ENGINE::ClientSize_Height };
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
        if (isSpace) //�����̽��� ���� ���� bool �� //������Ʈ�� ��ħ üũ
        {
            //Object* interObject = { nullptr }; //���� ��ȣ�ۿ� ������ �������� ��´�.
            interObject.clear(); // ������ ����ݴϴ�.

            //int inter_Count = ENGINE::ObjectMgr->InteractiveCheck_toPlayer(interObject, tmpRect);
            ENGINE::ObjectMgr->InteractiveCheck_toPlayer(&interObject, renderer->GetRect()); //��ȣ�ۿ��� ������ object�� �ε���

            if (interObject.size())
            {
                ENGINE::GUIMgr->SelectOptional(&interObject);
                //GUIMgr SelectOptional()���� ��ȣ�ۿ��� Object�� �ε����� ����
                //��ȣ�ۿ��� ������ object�� ���¸� ��ȯ��Ų��
                //ENGINE::ObjectMgr->ChangeActiveState(&interObject[ENGINE::GUIMgr->SelectOptional(&interObject, inter_Count)]);
                isSpace = false;
            }
            //isSpace = false;
        }
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

    //�÷��̾� ���� üũ ���ؼ�
    renderer->SetRect(); //��ǥ �̵��� ���� Rect ��ȭ

    prevState = state;
}


void Player::Inventory()
{
    // TODO::�÷��̾��� Ư���� �κ��丮 Ȯ�� ����
   // Character::CheckInventory(itemID);
}