#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

VOID Object::Initialize()
{
}

VOID Object::Update(const FLOAT& deltaTime)
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

VOID Object::Move(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::RIGHT:
        anim->Play(0);
        transform->position.x += moveSpeed * deltaTime;
        break;
    case Direction::LEFT:
        anim->Play(1);
        transform->position.x -= moveSpeed * deltaTime;
        break;
    }
}

VOID Object::Draw()
{
	renderer->Draw();
}

VOID Object::Release()
{
}