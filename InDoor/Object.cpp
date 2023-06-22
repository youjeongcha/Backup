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
{//TODO::애니메이션 있는 가구에 별도로 추가
    //활성, 비활성화 구분해서. 활성화 상태일때
    //TODO::애니메이션 재생할지, 아니면 이미지만 바꿀지 생각해봐야 함.

    //비활성화 상태이면 

    Operate(this);
    //TODO:: 보여줄 상태에 따라 출력 이미지 변화
    //if (prevState == State::Move) //'0'은 move 상태일때
    //{
    //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    //}


    switch (isActive)
    {
    case true:
        //renderer->ChangeSpritese(vResources[1]);
        //TODO::애니메이션 있는 가구에 별도로 추가
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