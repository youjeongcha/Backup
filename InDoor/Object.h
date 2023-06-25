#pragma once
#include <iostream>
#include <vector>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"


//오브젝트의 상태 네가지로 나뉜다.
//1.일반 움직이지 않는 오브젝트
//2.이동 가능 오브젝트
//3.애니메이션 있는 오브젝트
//4.상태 전환 있는 오브젝트(커튼,등불)
class Object : public ENGINE::GameObject
{
protected:
    std::string name;
    //std::vector<char> itemIDs;
    //std::string filePath;
    //std::vector<ENGINE::TotalResource> vResources; //리소스 뭉치

    //enum Data { SpritesX = 8, SpritesY = 4, SpritesX_Idle = 4, Speed = 200 };
    //리소스
    int SpritesX, SpritesY;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    //아이템 사용가능 조정/ 움직임 체크/ 애니메이션 체크/ 활성화 체크
    bool Available, isMove, isAnim, isActive;

    //인벤토리 들어올 수 있음 없음 체크 //TODO::가구 배치 가능하게 할거면 필요 없고

    //오브젝트의 가능 상태 네가지 
    enum class OBJECT_TYPE { NORMAL, MOVE, ANIM, ACTIVE };
    std::map<OBJECT_TYPE, bool> typeCheck; //오브젝트 종류(키), 해당 오브젝트의 작동 종류(bool)
   // std::vector<OBJECT_TYPE, bool> typeCheck;

    //OBJECT_TYPE::ACTIVE (등불 불 켜졌는지)
    //enum class State { ACTIVE, INACTIVE };
    //State state, prevState;

    //OBJECT_TYPE::MOVE
    enum class Direction { NONE, RIGHT, LEFT }; //오브젝트 자동 이동
    Direction dir; //이동 방향
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

