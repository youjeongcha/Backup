#include "Furniture.h"

Furniture::Furniture()
{
}

Furniture::~Furniture()
{
}

VOID Furniture::Initialize()
{
}

VOID Furniture::Update(const FLOAT& deltaTime)
{//TODO::�ִϸ��̼� �ִ� ������ ������ �߰�
    //Ȱ��, ��Ȱ��ȭ �����ؼ�. Ȱ��ȭ �����϶�
    //TODO::�ִϸ��̼� �������, �ƴϸ� �̹����� �ٲ��� �����غ��� ��.

    //��Ȱ��ȭ �����̸� 

    Operate(this);
//TODO:: ������ ���¿� ���� ��� �̹��� ��ȭ
//if (prevState == State::Move) //'0'�� move �����϶�
//{
//    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
//}


    switch (isActive)
    {
    case true:
        //renderer->ChangeSpritese(vResources[1]);
        //TODO::�ִϸ��̼� �ִ� ������ ������ �߰�
        //anim->SetChangeResouce(vResources[1]);
        break;
    case false:
        //renderer->ChangeSpritese(vResources[1]);
        break;
    }
}

//VOID Furniture::Move(const FLOAT& deltaTime)
//{
//
//    //switch (dir)
//    //{
//    //case Direction::Right:
//    //    anim->Play(0);
//    //    transform->position.x += Speed * deltaTime;
//    //    break;
//    //case Direction::Left:
//    //    anim->Play(1);
//    //    transform->position.x -= Speed * deltaTime;
//    //    break;
//    //}
//}

VOID Furniture::SetScale(const Vector2& scale)
{
	return VOID();
}