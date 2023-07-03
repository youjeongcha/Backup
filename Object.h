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

struct EachObjectIndex
{//�ش� object�� Ư���س��� ���� ��ҵ�
    std::string name;
    int mapIndex, eachObjectIndex; //��� ���� ������� //�ʿ��� �ش� object �ȿ����� ��ȣ
};

struct EachObject
{
    //int mapIndex, index; //��� ���� ������� //�ʿ��� �ش� object �ȿ����� ��ȣ
    EachObjectIndex obejctIndex;
    bool Available, isMove, isAnim, isActive;
    float x, y, move_X, move_Y, move_Speed;
};

struct ObjectData
{
    //std::string name;
    std::map<OBJECT_TYPE, bool> typeCheck;
    int spritesX, spritesY;
    std::string fileName;

    int objectCount; //�ش� ������Ʈ�� �� ����

    //objectData(Door)�ȿ� �ش� ��� eachObject���� �����͵��� ������ �ִ�
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
    //std::string name;
    //int mapIndex, index; //mapIndex �ش� Object�� �Ҽ� Map //map + �ش� Object������ Index ��ȣ
    EachObjectIndex eachObjectIndex;

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
    Object& operator=(const Object& other) {
        // �Ҵ� �������� ������ �����մϴ�
        // ������ ��� �������� other�� ��� ���� ������ �Ҵ��մϴ�
        // �ʿ信 ���� ���� ���� �Ǵ� ���� ���縦 �����ؾ� �մϴ�
        // ��ȯ������ *this�� ��ȯ�մϴ�

        eachObjectIndex = other.eachObjectIndex;

        //���ҽ�
        SpritesX = other.SpritesX;
        SpritesY = other.SpritesY;

        renderer = other.renderer;
        anim = other.anim;

        //������ ��밡�� ����/ ������ üũ/ �ִϸ��̼� üũ/ Ȱ��ȭ üũ
        Available = other.Available;
        isMove = other.isMove;
        isAnim = other.isAnim;
        isActive = other.isActive;

        //�κ��丮 ���� �� ���� ���� üũ //TODO::���� ��ġ �����ϰ� �ҰŸ� �ʿ� ����

        //������Ʈ�� ���� ���� �װ��� 
        typeCheck = other.typeCheck; //������Ʈ ����(Ű), �ش� ������Ʈ�� �۵� ����(bool)

        //OBJECT_TYPE::MOVE
        dir = other.dir; //�̵� ����
        moveSpeed = other.moveSpeed;

        return *this;
    }

    Object();
	Object(const ObjectData& dataSet, int index); //���ϱ��� �ε���(���Ͽ��� ��ü�� ���� ������� �ִ� ��)//��ü �ϳ��� ���� ����Ѵ�.
	~Object();

   // virtual VOID Initialize() abstract;
    virtual VOID Initialize();
    //virtual VOID Update(const FLOAT& deltaTime) abstract;
    VOID Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime);
   // virtual VOID Move(const FLOAT& deltaTime) abstract;
    VOID Draw();
    VOID Release();

    //������Ʈ ��Ĩ �Ǵ�
    RECT GetRect() { return renderer->GetRect(); } //��ȯ���� const ������ ����


    //���� ����
    void ChangeActiveState(); //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.

    EachObjectIndex GetEachObjectIndex() { return eachObjectIndex; }


    //ENGINE::RECT* GetRect() { return &renderer->GetRect(); }
    //Vector2 GetPos() { return renderer->GetPos(); }
    //SIZE GetSize() { return renderer->GetDrawSize(); }
};

