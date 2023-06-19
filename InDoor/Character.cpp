#include "Character.h"
#include "ResourceManager.h"
#include "SceneManager.h"

/*
int main() {
    Player player("John", { 1, 2, 3 }, "player_file.txt");
    player.CheckInventory(2);

    NPC npc("Bob", { 4, 5, 6 }, "npc_file.txt");
    npc.CheckInventory(7);

    return 0;
}
*/

Character::Character() 
{
    //nowKeyState.currentKey = ' ';
    //nowKeyState.currentState = '1'; //idle 상태
}

//Character::Character(const std::string& charName, const std::vector<char>& items)
//{
//    state = State::Idle;
//    dir = Direction::Right;
//
//    ENGINE::ResourceMgr->Load("Player.bmp");
//
//    renderer = new ENGINE::SpriteRenderer("Player.bmp", SpritesX, SpritesY);
//    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
//    renderer->SetScale(transform->scale.x, transform->scale.y);
//    AddComponent(renderer);
//    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
//
//    ENGINE::InputComponent* input = new ENGINE::InputComponent;
//    input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
//    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
//    AddComponent(input);
//}

Character::~Character()
{
}

VOID Character::SetScale(const Vector2& scale)
{
    GameObject::SetScale(scale);

    if (renderer) 
        renderer->SetScale(scale.x, scale.y);
}

VOID Character::Initialize()
{
    transform->position = { 400, 600 };
}

VOID Character::Release()
{
}

VOID Character::Update(const FLOAT& deltaTime)
{
    Operate(this); //


    //nowKeyState = input->GetKeyCheck();

    //key를 떼면 state가 idle 상태로 벼한다. -> 스프라이트도 idle 상태로 변경되어야 한다.
    //renderer->ChangeSpritese(vResources[0]); //idle

    switch (state)
    {
    case State::Move:
        renderer->ChangeSpritese(vResources[1]);
        anim->SetChangeResouce(vResources[1]);
        Move(deltaTime);
        break;
    case State::Idle:

        if (prevState == State::Move) //'0'은 move 상태일때
        {
            renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
            renderer->ChangeSpritese(vResources[0]); //idle //TODO::이거 왼오 나눠야 함
            anim->SetChangeResouce(vResources[0]);
        }
        //key를 떼면 state가 idle 상태로 벼한다. -> 스프라이트도 idle 상태로 변경되어야 한다.
        //anim->Play();
        break;
    }

    //스프라이트 왼오 나눠서 애니메이션 플레이
    switch (dir)
    { 
    case Direction::Right:
        anim->Play(0);
        break;
    case Direction::Left:
        anim->Play(1);
        break;
    }

    prevState = state;
}

VOID Character::Draw()
{
    renderer->Draw();
}

VOID Character::Move(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::Right:
        // 이미지 변경
        //renderer->ChangeSpritese(vResources[1]);  //TODO::전환되는 한번의 포인트를 찾는다. //TODO::버튼을 누르고 있을때 작동되도록 //TODO::idle 왼오 나누어야 함
        //anim->SetChangeResouce(vResources[1]);
        // 애니메이션 재생
        //anim->Play(0);
        transform->position.x += Speed * deltaTime;
        break;
    case Direction::Left:
        // 이미지 변경
       // renderer->ChangeSpritese(vResources[1]);
        //anim->SetChangeResouce(vResources[1]);
        // 애니메이션 재생
        //anim->Play(1);
        transform->position.x -= Speed * deltaTime;
        break;
    }
}

void Character::CheckInventory(int itemID) const
{
    bool hasItem = false;
    for (int id : itemIDs) {
        if (id == itemID) {
            hasItem = true;
            break;
        }
    }

    if (hasItem) {

    }
    else {

    }
}
