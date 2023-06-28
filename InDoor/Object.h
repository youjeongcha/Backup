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
    int mapIndex; //사용 맵이 어디인지
    bool Available, isMove, isAnim, isActive;
    float x, y, move_X, move_Y, move_Speed;
};

struct ObjectData
{
    std::string name;
    std::map<OBJECT_TYPE, bool> typeCheck;
    int spritesX, spritesY;
    std::string fileName;

    int objectCount; //해당 오브젝트의 총 수량

    EachObject* eachObject;
};


//오브젝트의 상태 네가지로 나뉜다.
//1.일반 움직이지 않는 오브젝트
//2.이동 가능 오브젝트
//3.애니메이션 있는 오브젝트
//4.상태 전환 있는 오브젝트(커튼,등불)
class Object : public ENGINE::GameObject
{
protected:
    std::string name;
    int mapIndex;

    //리소스
    int SpritesX, SpritesY;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    //아이템 사용가능 조정/ 움직임 체크/ 애니메이션 체크/ 활성화 체크
    bool Available, isMove, isAnim, isActive;

    //인벤토리 들어올 수 있음 없음 체크 //TODO::가구 배치 가능하게 할거면 필요 없고

    //오브젝트의 가능 상태 네가지 
    std::map<OBJECT_TYPE, bool> typeCheck; //오브젝트 종류(키), 해당 오브젝트의 작동 종류(bool)

    //OBJECT_TYPE::MOVE
    enum class Direction { NONE, RIGHT, LEFT }; //오브젝트 자동 이동
    Direction dir; //이동 방향
    int moveSpeed;


public:
    Object();
	Object(const ObjectData& dataSet, int index); //객체 하나만 정보 줘야해서
	~Object();

    virtual VOID Initialize() abstract;
    //virtual VOID Update(const FLOAT& deltaTime) abstract;
    VOID Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime) abstract;
    VOID Draw();
    VOID Release();

    //컴포넌트 겹칩 판단
    RECT GetRect() { return renderer->GetRect(); } //반환형에 const 한정자 지정


    //상태 변경
    bool ChangeActiveState(); //TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.


    //ENGINE::RECT* GetRect() { return &renderer->GetRect(); }
    //Vector2 GetPos() { return renderer->GetPos(); }
    //SIZE GetSize() { return renderer->GetDrawSize(); }
};

