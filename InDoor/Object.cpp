#include "Object.h"
#include "ResourceManager.h"

Object::Object()
{
}

Object::Object(const ObjectData& dataSet, int eachObjectindex)
{
    eachObjectIndex.name = dataSet.eachObject[eachObjectindex].obejctIndex.name;
    //������Ʈ Ÿ�� ����
    typeCheck = dataSet.typeCheck;
    //���ҽ�
    SpritesX = dataSet.spritesX;
    SpritesY = dataSet.spritesY;

    //Objeect ����
    eachObjectIndex.mapIndex = dataSet.eachObject[eachObjectindex].obejctIndex.mapIndex;
    eachObjectIndex.eachObjectIndex = dataSet.eachObject[eachObjectindex].obejctIndex.eachObjectIndex;

    Available = dataSet.eachObject[eachObjectindex].Available;
    isMove = dataSet.eachObject[eachObjectindex].isMove;
    isAnim = dataSet.eachObject[eachObjectindex].isAnim;
    isActive = dataSet.eachObject[eachObjectindex].isActive;

    ENGINE::ResourceMgr->Load(dataSet.fileName);

    renderer = new ENGINE::SpriteRenderer(dataSet.fileName.c_str(), SpritesX, SpritesY);
    renderer->SetPos(dataSet.eachObject->x, dataSet.eachObject->y);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    AddComponent(renderer);

    //Anim ����
    if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move ����
    dir = (Direction)dataSet.eachObject[eachObjectindex].move_X; //TODO::�̰� 
    //dir = (Direction)dataSet.eachObject[index].move_Y; //move_Y �κе� �ش� �ǰ�
    moveSpeed = dataSet.eachObject[eachObjectindex].move_Speed;
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

    //Operate(this);
    //TODO:: ������ ���¿� ���� ��� �̹��� ��ȭ
    //if (prevState == State::Move) //'0'�� move �����϶�
    //{
    //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    //}

    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    else
        renderer->SetSrc(0, 0);

    renderer->SetRect(); //��ǥ �̵��� ���� Rect ��ȭ
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

bool Object::ChangeActiveState()
{ 
    isActive = !isActive; 

    return isActive;
}

VOID Object::Release()
{
}