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
    input->AddBinding(VK_SPACE, [&]() {  isSpace = true; state = State::Idle; }, [&]() { isSpace = false; state = State::Idle; }); //스페이스
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
        if (isSpace) //스페이스를 누른 상태 bool 값 //오브젝트와 겹침 체크
        {
            //Object* interObject = { nullptr }; //현재 상호작용 가능한 가구들을 담는다.
            interObject.clear(); // 변수를 비워줍니다.

            ENGINE::ObjectMgr->InteractiveCheck_toPlayer(&interObject, renderer->GetRect()); //상호작용이 가능한 object의 인덱스

            if (interObject.size())
            {
                ENGINE::GUIMgr->SelectOptional(&interObject);
                //GUIMgr SelectOptional()에서 상호작용할 Object의 인덱스를 선별
                //상호작용이 가능한 object의 상태를 변환시킨다
                //ENGINE::ObjectMgr->ChangeActiveState(&interObject[ENGINE::GUIMgr->SelectOptional(&interObject, inter_Count)]);
                isSpace = false;
            }
            //isSpace = false;
        }
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

    //플레이어 범위 체크 위해서
    renderer->SetRect(); //좌표 이동에 따라 Rect 변화

    prevState = state;
}