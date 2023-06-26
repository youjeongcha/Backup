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
    transform->position = { ENGINE::ClientSize_Width / 2,  ENGINE::ClientSize_Height };
}

VOID Character::Release()
{
}

VOID Character::Update(const FLOAT& deltaTime)
{
    //Operate(this);

    ////key를 떼면 state가 idle 상태로 벼한다. -> 스프라이트도 idle 상태로 변경되어야 한다.
    ////renderer->ChangeSpritese(vResources[0]); //idle

    //switch (state)
    //{
    //case State::Move:
    //    //renderer->ChangeSpritese(vResources[1]);
    //    //anim->SetChangeResouce(vResources[1]);
    //    Move(deltaTime);
    //    break;
    //case State::Idle:

    //    //if (prevState == State::Move) //'0'은 move 상태일때
    //    //{
    //    //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    //    //}
    //    break;
    //}

    ////스프라이트 왼오 나눠서 애니메이션 플레이
    //switch (dir)
    //{ 
    //case Direction::Right:
    //    anim->Play(0 + (int)state * 2);
    //    break;
    //case Direction::Left:
    //    anim->Play(1 + (int)state * 2);
    //    break;
    //}

    //prevState = state;
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
        anim->Play(0);
        transform->position.x += Speed * deltaTime;
        break;
    case Direction::Left:
        anim->Play(1);
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