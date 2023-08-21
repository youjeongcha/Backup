#include "Character.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Character::Character() 
{
}

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

    renderer->SetRect(); //좌표 이동에 따라 Rect 변화
}

//void Character::CheckInventory(int itemID) const
//{
//    bool hasItem = false;
//    for (int id : itemIDs) {
//        if (id == itemID) {
//            hasItem = true;
//            break;
//        }
//    }
//
//    if (hasItem) {
//
//    }
//    else {
//
//    }
//}