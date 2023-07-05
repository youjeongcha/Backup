#include "Object.h"
#include "ResourceManager.h"

Object::Object()
{
}

Object::Object(const ObjectData& dataSet, int index)
{
    eachObjectIndex.name = dataSet.eachObject[index].objectIndex.name;
    //������Ʈ Ÿ�� ����
    typeCheck = dataSet.typeCheck;
    //���ҽ�
    SpritesX = dataSet.spritesX;
    SpritesY = dataSet.spritesY;

    //������Ʈ ��Ī
    objectname = dataSet.objectName;
    //���ϸ�
    fileName = dataSet.fileName;

    //Objeect ����
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
    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    AddComponent(renderer);

    //Anim ����
    if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move ����
    dir = (Direction)dataSet.eachObject[index].move_X; //TODO::�̰� 
    //dir = (Direction)dataSet.eachObject[index].move_Y; //move_Y �κе� �ش� �ǰ�
    moveSpeed = dataSet.eachObject[index].move_Speed;
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

    //if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
    //    renderer->SetSrc(0, 1);
    //else
    //    renderer->SetSrc(0, 0);

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

void Object::ChangeActiveState()
{ 
    isActive = !isActive; 

    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    else
        renderer->SetSrc(0, 0);

    //return isActive;
}

VOID Object::Release()
{
}