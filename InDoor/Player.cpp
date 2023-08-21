#include "Player.h"
#include "GameManager.h"

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
    input->AddBinding(VK_SPACE, [&]() {  isSpace = true; state = State::Idle; }, [&]() { isSpace = false; state = State::Idle; }); //�����̽�
    input->AddBinding(VK_I, [&]() {  GameMgr->SetIsInventory(true); state = State::Idle; }, [&]() { GameMgr->SetIsInventory(false); state = State::Idle; }); 

    AddComponent(input);
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