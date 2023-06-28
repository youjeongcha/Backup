#pragma once
#include <iostream>
#include <vector>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"

enum class OBJECT_TYPE
{
    NORMAL,
    MOVE,
    ANIM,
    ACTIVE,
    TYPE_COUNT
};

struct EachObject
{
    int mapIndex; //��� ���� �������
    bool Available, isMove, isAnim, isActive;
    float x, y, move_X, move_Y, move_Speed;
};

struct ObjectData
{
    std::string name;
    std::map<OBJECT_TYPE, bool> typeCheck;
    int spritesX, spritesY;
    std::string fileName;

    int objectCount; //�ش� ������Ʈ�� �� ����

    EachObject* eachObject;
};


//������Ʈ�� ���� �װ����� ������.
//1.�Ϲ� �������� �ʴ� ������Ʈ
//2.�̵� ���� ������Ʈ
//3.�ִϸ��̼� �ִ� ������Ʈ
//4.���� ��ȯ �ִ� ������Ʈ(Ŀư,���)
class Object : public ENGINE::GameObject
{
protected:
    std::string name;
    int mapIndex;

    //���ҽ�
    int SpritesX, SpritesY;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    //������ ��밡�� ����/ ������ üũ/ �ִϸ��̼� üũ/ Ȱ��ȭ üũ
    bool Available, isMove, isAnim, isActive;

    //�κ��丮 ���� �� ���� ���� üũ //TODO::���� ��ġ �����ϰ� �ҰŸ� �ʿ� ����

    //������Ʈ�� ���� ���� �װ��� 
    std::map<OBJECT_TYPE, bool> typeCheck; //������Ʈ ����(Ű), �ش� ������Ʈ�� �۵� ����(bool)

    //OBJECT_TYPE::MOVE
    enum class Direction { NONE, RIGHT, LEFT }; //������Ʈ �ڵ� �̵�
    Direction dir; //�̵� ����
    int moveSpeed;


public:
    Object();
	Object(const ObjectData& dataSet, int index); //��ü �ϳ��� ���� ����ؼ�
	~Object();

    virtual VOID Initialize() abstract;
    //virtual VOID Update(const FLOAT& deltaTime) abstract;
    VOID Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime) abstract;
    VOID Draw();
    VOID Release();

    //������Ʈ ��Ĩ �Ǵ�
    RECT GetRect() { return renderer->GetRect(); } //��ȯ���� const ������ ����


    //���� ����
    bool ChangeActiveState(); //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.


    //ENGINE::RECT* GetRect() { return &renderer->GetRect(); }
    //Vector2 GetPos() { return renderer->GetPos(); }
    //SIZE GetSize() { return renderer->GetDrawSize(); }
};

