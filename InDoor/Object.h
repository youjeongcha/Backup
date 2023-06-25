#pragma once
#include <iostream>
#include <vector>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"


//������Ʈ�� ���� �װ����� ������.
//1.�Ϲ� �������� �ʴ� ������Ʈ
//2.�̵� ���� ������Ʈ
//3.�ִϸ��̼� �ִ� ������Ʈ
//4.���� ��ȯ �ִ� ������Ʈ(Ŀư,���)
class Object : public ENGINE::GameObject
{
protected:
    std::string name;
    //std::vector<char> itemIDs;
    //std::string filePath;
    //std::vector<ENGINE::TotalResource> vResources; //���ҽ� ��ġ

    //enum Data { SpritesX = 8, SpritesY = 4, SpritesX_Idle = 4, Speed = 200 };
    //���ҽ�
    int SpritesX, SpritesY;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    //������ ��밡�� ����/ ������ üũ/ �ִϸ��̼� üũ/ Ȱ��ȭ üũ
    bool Available, isMove, isAnim, isActive;

    //�κ��丮 ���� �� ���� ���� üũ //TODO::���� ��ġ �����ϰ� �ҰŸ� �ʿ� ����

    //������Ʈ�� ���� ���� �װ��� 
    enum class OBJECT_TYPE { NORMAL, MOVE, ANIM, ACTIVE };
    std::map<OBJECT_TYPE, bool> typeCheck; //������Ʈ ����(Ű), �ش� ������Ʈ�� �۵� ����(bool)
   // std::vector<OBJECT_TYPE, bool> typeCheck;

    //OBJECT_TYPE::ACTIVE (��� �� ��������)
    //enum class State { ACTIVE, INACTIVE };
    //State state, prevState;

    //OBJECT_TYPE::MOVE
    enum class Direction { NONE, RIGHT, LEFT }; //������Ʈ �ڵ� �̵�
    Direction dir; //�̵� ����
    int moveSpeed;


public:
	Object();
	~Object();

    virtual VOID Initialize() abstract;
    //virtual VOID Update(const FLOAT& deltaTime) abstract;
    VOID Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime) abstract;
    VOID Draw();
    VOID Release();
};

