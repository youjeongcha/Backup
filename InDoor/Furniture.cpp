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