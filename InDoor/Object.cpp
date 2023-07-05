#include "Object.h"
#include "ResourceManager.h"

Object::Object()
{
}

Object::Object(const ObjectData& dataSet, int index)
{
    eachObjectIndex.name = dataSet.eachObject[index].objectIndex.name;
    //오브젝트 타입 설정
    typeCheck = dataSet.typeCheck;
    //리소스
    SpritesX = dataSet.spritesX;
    SpritesY = dataSet.spritesY;

    //오브젝트 명칭
    objectname = dataSet.objectName;
    //파일명
    fileName = dataSet.fileName;

    //Objeect 개별
    eachObjectIndex.mapIndex = dataSet.eachObject[index].objectIndex.mapIndex;
    eachObjectIndex.eachObjectIndex = dataSet.eachObject[index].objectIndex.eachObjectIndex;

    Available = dataSet.eachObject[index].Available;
    isMove = dataSet.eachObject[index].isMove;
    isAnim = dataSet.eachObject[index].isAnim;
    isActive = dataSet.eachObject[index].isActive;

    ENGINE::ResourceMgr->Load(dataSet.fileName);

    renderer = new ENGINE::SpriteRenderer(dataSet.fileName.c_str(), SpritesX, SpritesY);
    renderer->SetPos(dataSet.eachObject->x, dataSet.eachObject->y);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    if (isActive) //작동 여부에 따라 이미지 다르게
        renderer->SetSrc(0, 1);
    AddComponent(renderer);

    //Anim 관련
    if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move 관련
    dir = (Direction)dataSet.eachObject[index].move_X; //TODO::이거 
    //dir = (Direction)dataSet.eachObject[index].move_Y; //move_Y 부분도 해당 되게
    moveSpeed = dataSet.eachObject[index].move_Speed;
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

    //Operate(this);
    //TODO:: 보여줄 상태에 따라 출력 이미지 변화
    //if (prevState == State::Move) //'0'은 move 상태일때
    //{
    //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    //}

    //if (isActive) //작동 여부에 따라 이미지 다르게
    //    renderer->SetSrc(0, 1);
    //else
    //    renderer->SetSrc(0, 0);

    renderer->SetRect(); //좌표 이동에 따라 Rect 변화
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

void Object::ChangeActiveState()
{ 
    isActive = !isActive; 

    if (isActive) //작동 여부에 따라 이미지 다르게
        renderer->SetSrc(0, 1);
    else
        renderer->SetSrc(0, 0);

    //return isActive;
}

VOID Object::Release()
{
}