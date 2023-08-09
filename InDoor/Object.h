#pragma once
#include <iostream>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"

enum OBJECT_TYPE
{
    NORMAL,
    TIMECHANGE, //�㳷�� ���� �̹��� ��ȯ
    ANIM,
    ACTIVE,
    INTERACTIVE, //��ȣ�ۿ� ����
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
    EachObjectIndex objectIndex;
    bool Available, isMove, isAnim, isActive;
    float x, y, move_X, move_Y, move_Speed;
};

struct ObjectData
{
    //objectData(Door)�ȿ� �ش� ��� eachObject���� �����͵��� ������ �ִ�
    std::vector<EachObject*> eachObject;


    std::map<OBJECT_TYPE, bool> typeCheck;
    int spritesX, spritesY;

    std::string objectName;
    std::string fileName;

    int objectCount; //�ش� ������Ʈ�� �� ����


    //---�� ��ȣ�ۿ� ����---
    int detailSelectCount; //�� ������ ����(��� ��ư�� �������Ͽ� ī��Ʈ)
    std::vector<std::string> sDetailSelect;
};

enum FRUITS_GROWTH
{
    SOIL,
    SEDDS,
    FLOWERS,
    FRUITS,
    FRUITS_GROWTH_END
};

class Object;
//���±�� ����
class State
{
public:
    virtual ~State() {}

    virtual void Enter(Object*) abstract;
    virtual void Excute(Object*) abstract;
    virtual void Exit(Object*) abstract;
};



//������Ʈ�� ���� �װ����� ������.
//1.�Ϲ� �������� �ʴ� ������Ʈ
//2.�̵� ���� ������Ʈ
//3.�ִϸ��̼� �ִ� ������Ʈ
//4.���� ��ȯ �ִ� ������Ʈ(Ŀư,���)
 class Object abstract : public ENGINE::GameObject
{
protected:
    //std::string name;
    //int mapIndex, index; //mapIndex �ش� Object�� �Ҽ� Map //map + �ش� Object������ Index ��ȣ
    EachObjectIndex eachObjectIndex;

    //���� �������� ��ȣ�ۿ� �����Ѱ�? //���� ������̾���� �÷��̾�� ��ġ���� Ȯ���ϱ� ����
    bool isUse;
    //���� ������ �ִ� �������� �ִ���
    bool isHaveItem;

    //��Ī
    std::string objectName;
    //���ϸ�
    std::string fileName;

    //���ҽ�
    int spritesX, spritesY;

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


    //---�� ��ȣ�ۿ� ����---
    int detailSelectCount; //�� ������ ����(��� ��ư�� �������Ͽ� ī��Ʈ)
    ENGINE::UIImage* detailSelect_UI;
    std::vector<std::string> sDetailSelect;

public:
    Object(const Object& other) {
        // ��� �������� ���� ����
        eachObjectIndex = other.eachObjectIndex;
        isUse = other.isUse;
        isHaveItem = other.isHaveItem;

        objectName = other.objectName;
        fileName = other.fileName;
        spritesX = other.spritesX;
        spritesY = other.spritesY;
        Available = other.Available;
        isMove = other.isMove;
        isAnim = other.isAnim;
        isActive = other.isActive;
        typeCheck = other.typeCheck;
        dir = other.dir;
        moveSpeed = other.moveSpeed;
        //�� ������
        detailSelectCount = other.detailSelectCount;
        detailSelect_UI = other.detailSelect_UI;
        sDetailSelect = other.sDetailSelect;

        // renderer�� ���� ����
        AddComponent(renderer = new ENGINE::SpriteRenderer(*other.renderer));

        //transform = other.transform;

        transform->position = { other.transform->position.x,  other.transform->position.y };

        if (typeCheck.find(ANIM)->second) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
            AddComponent(anim = new ENGINE::SpriteAnimation(spritesX , spritesY));
        else
            anim = NULL;
        //renderer = new ENGINE::SpriteRenderer(*other.renderer);
        // anim�� �ʿ��� ��� ���� ����
        //if (other.anim)
        //    anim = new ENGINE::AnimationComponent(*other.anim);
        //else
        //    anim = nullptr;
    }

    //Object& Object::operator=(const Object& other)
    //{
    //    if (this == &other)
    //        return *this;

    //    // ��� �������� ���� ����
    //    eachObjectIndex = other.eachObjectIndex;
    //    objectName = other.objectName;
    //    fileName = other.fileName;
    //    SpritesX = other.SpritesX;
    //    SpritesY = other.SpritesY;
    //    Available = other.Available;
    //    isMove = other.isMove;
    //    isAnim = other.isAnim;
    //    isActive = other.isActive;
    //    typeCheck = other.typeCheck;
    //    dir = other.dir;
    //    moveSpeed = other.moveSpeed;

    //    // renderer�� ���� ����
    //    delete renderer;
    //    renderer = new ENGINE::SpriteRenderer(*other.renderer);

    //    delete anim;
    //    anim = other.anim ? new ENGINE::AnimationComponent(*other.anim) : nullptr;

    //    return *this;
    //}
    /*
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
    }*/

    Object();
	Object(const ObjectData& dataSet, int index); //���ϱ��� �ε���(���Ͽ��� ��ü�� ���� ������� �ִ� ��)//��ü �ϳ��� ���� ����Ѵ�.
	~Object();

    virtual VOID Initialize();
    //VOID Update(const FLOAT& deltaTime);
    virtual void Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime);
    virtual VOID Draw();
    VOID Release();

    //������Ʈ ��Ĩ �Ǵ�
    RECT GetRect() { return renderer->GetRect(); } //��ȯ���� const ������ ����
    EachObjectIndex GetEachObjectIndex() { return eachObjectIndex; }
    std::string GetObjectName() { return objectName; }

    //���� �����(�ʿ��� ����)�̾���� �÷��̾�� ��ġ���� Ȯ���ϱ� ����
    bool GetisUse() { return isUse; }

    //---������ ����----
    void DetailSelectForm(); //���� ������ ��� Ʋ
    virtual void DetailSelect(int selectNum) abstract; //��� Ʋ�� ���� ��ü�� �Լ� //������ ������� DetailSelectForm �ʿ� �۵� �����ʸ� �ֱ� ���� �Լ�
    //���� ����
    void ChangeActiveState(); //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.
    void CancelBtnClickHandler();
    bool IsInteractive() { return typeCheck.find(INTERACTIVE)->second; } //��ȣ�ۿ� ������ Object���� Ȯ��

    //�㳷 ��ȭ�� ���� �̹��� ����
    void MoringNight_TimeChangeBitmap();
    //�ð��� ����� ���� �̹��� ����(ex.�Ĺ� ����)
    virtual void PassOfthe_TimeChangeBitmap();
    //ENGINE::RECT* GetRect() { return &renderer->GetRect(); }
    //Vector2 GetPos() { return renderer->GetPos(); }
    //SIZE GetSize() { return renderer->GetDrawSize(); }
};

